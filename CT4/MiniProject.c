//PhoneBook
#include <stdio.h>
#include <string.h>

struct PhoneBook{
    char Name[40];
    char Address[200];
    char PhoneNo[10];
    char City[30];
    char State[30];
    char Country[30];
};

struct PhoneBook pb[100000];
int startValue[26] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int charsize[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int maxValue = 0;

int exists(char Name[],char Address[],char PhoneNo[],char City[],char State[],char Country[]){
    int n = (int)Name[0]-97;  //ascii a=97 b = 98 therefore acsii-97 is order
    if(startValue[n] == -1) return 0;
    for(int i=startValue[n];i<(n<25?startValue[n+1]:100000);i++){
        if(pb[i].Name == Name){
            if(pb[i].Address == Address){
                if(pb[i].PhoneNo == PhoneNo){
                    if(pb[i].City == City){
                        if(pb[i].Country == Country){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void sort(int start,int stop){
    int size = stop-start;
    for(int i =0;i<size;i++){
        for(int j=start;j<stop-i;j++){
            struct PhoneBook temp1 = pb[j],temp2 = pb[j+1];
            if(strcmp(temp1.Name,temp2.Name) < 0) continue;
            else if(strcmp(temp1.Name,temp2.Name)>0){
                pb[j] = temp2;pb[j+1] = temp1;
            } 
            else if(strcmp(temp1.Name,temp2.Name) == 0){
                if (strcmp(temp1.Address,temp2.Address) < 0) continue;
                else if(strcmp(temp1.Address,temp2.Address)>0){
                    pb[j] = temp2;pb[j+1] = temp1;
                } 
                else if(strcmp(temp1.Address,temp2.Address) == 0){
                    if(strcmp(temp1.PhoneNo,temp2.PhoneNo) < 0) continue;
                    else if(strcmp(temp1.PhoneNo,temp2.PhoneNo)>0){
                    pb[j] = temp2;pb[j+1] = temp1;
                    } 
                    else if(strcmp(temp1.PhoneNo,temp2.PhoneNo) == 0){
                        if(strcmp(temp1.City,temp2.City) < 0) continue;
                        else if(strcmp(temp1.City,temp2.City)>0){
                        pb[j] = temp2;pb[j+1] = temp1;
                        } 
                        else if(strcmp(temp1.City,temp2.City) == 0){
                            if(strcmp(temp1.State,temp2.State) < 0) continue;
                            else if(strcmp(temp1.State,temp2.State)>0){
                            pb[j] = temp2;pb[j+1] = temp1;
                            } 
                            else if(strcmp(temp1.State,temp2.State) == 0){
                                if(strcmp(temp1.Country,temp2.Country) < 0) continue;
                                else if(strcmp(temp1.Country,temp2.Country)>0){
                                pb[j] = temp2;pb[j+1] = temp1;
                                return;
                                }
                            } 
                        } 
                    } 
                }   
            } 
            
        }
    }
}

void AddSpot(int spotValue,int charValue){
    //make empty space and also change startValue array
    maxValue++;
    for(int i = maxValue;i>spotValue;i--){
        pb[i] = pb[i-1];
    }
    for(int i =0;i<26;i++){
        if(startValue[i] == -1 && i==charValue){
            startValue[i] =spotValue;
            charsize[i]++;
        }else if(startValue[i] >= spotValue && startValue[i] != -1){
            //startValue[i]++;
            charsize[i]++;
        }
    }
}

void Add(char* Name,char* Address,char* PhoneNo,char* City,char* State,char* Country){
    if(!exists(Name,Address,PhoneNo,City,State,Country)){
        int n = (int) Name[0]- 97;
        int spotValue = -1;
        if(startValue[n] == -1){
            for(int i = n;i<26;i++){
                if(startValue[i] != -1){
                    spotValue = startValue[i];
                    break;
                }
            }
            for(int i = n;i>=0;i--){
                if(startValue[i] != -1){
                    spotValue = startValue[i]+charsize[i];
                    break;
                }
            }
            if(spotValue==-1){ 
                spotValue=0;
            }
            AddSpot(spotValue,n);
        }else{
            AddSpot(startValue[n],n);
            spotValue = startValue[n];
        }
        strcpy(pb[spotValue].Name,Name);
        strcpy(pb[spotValue].Address,Address);
        strcpy(pb[spotValue].PhoneNo,PhoneNo);
        strcpy(pb[spotValue].City,City);
        strcpy(pb[spotValue].State,State);
        strcpy(pb[spotValue].Country,Country);
        sort(startValue[n],startValue[n]+charsize[n]-1);
        printf("Record Added");
        return;
    }
    printf("Record Already exists\n");
}

void RemoveSpot(int spotValue){
    int charValue = (int) pb[spotValue].Name[0]-97;
    for(int i = spotValue;i<maxValue;i++){
        pb[i] = pb[i+1];
    }
    struct PhoneBook temp = {"","","","","",""};
    pb[maxValue] = temp;
    charsize[charValue]--;
    for(int i = charValue+1;i<26;i++){
        startValue[i]--;
    }
    maxValue--;
}

void Remove(char* Name){
    int n = (int) Name[0]-97;
    if(charsize[n] == 0){
        printf("No Record with Name %s Exists to Delete\n",Name);
        return;
    }else{
        struct PhoneBook tempbook[charsize[n]];
        int tempspot[charsize[n]];
        int count = 0,choice;;
        for(int i = startValue[n];i<startValue[n]+charsize[n];i++){
            if(strcmp(pb[i].Name,Name) == 0){
                tempbook[count] = pb[i];
                tempspot[count] = i;
                count++;
                
            }
        }
        if(count==1){
            RemoveSpot(tempspot[0]);
            printf("Record Deleted\n");
        }else if(count >1){
            printf("Multiple Records with Same name Available Choose the Number to Delete\n");
            printf("---------------------------------------------------------------------------------------\n");
            printf("      Name        Address        PhoneNo       City        State       Country\n");
            for(int i = 0;i<count;i++){
                struct PhoneBook t = tempbook[i];//temp var
                printf("%d %10s %10s %10s %10s %10s %10s\n",i,t.Name,t.Address,t.PhoneNo,t.City,t.State,t.Country);
            }
            printf("---------------------------------------------------------------------------------------\n");
            scanf("%d",&choice);
            printf("\n");
            if(choice >=count){
                printf("Choice invalid Aborting delete operation\n");
                return;
            }
            else{
                RemoveSpot(tempspot[choice]);
                printf("\n\n Record Deleted\n");
            }
            
        }
    }
    
}

void Display(int start,int stop){
    if(maxValue == 0){
        printf("PhoneBook Empty\n");
    }else{
    printf("---------------------------------------------------------------------------------------\n");
    printf("S.No      Name        Address        PhoneNo       City        State       Country\n");
    for(int i = start;i<stop;i++){
        struct PhoneBook t = pb[i];//temp var
        printf("%d %10s %10s %10s %10s %10s %10s\n",i+1,t.Name,t.Address,t.PhoneNo,t.City,t.State,t.Country);
    }
    printf("---------------------------------------------------------------------------------------\n");
    }
}

void Search(char* Name){
    int n = (int) Name[0] - 97;
    struct PhoneBook tempbook[charsize[n]];
    int tempspot[charsize[n]];
    printf("---------------------------------------------------------------------------------------\n");
    printf("      Name        Address        PhoneNo       City        State       Country\n");
    for(int i = startValue[n];i<startValue[n]+charsize[n];i++){
        if(strcmp(pb[i].Name,Name) == 0){
        struct PhoneBook t = pb[i];//temp var
        printf("%10s %10s %10s %10s %10s %10s\n",t.Name,t.Address,t.PhoneNo,t.City,t.State,t.Country);
        }
    }
    printf("---------------------------------------------------------------------------------------\n");
    
}

void DisplayMenu(){
    printf("\n\n---------------------------------MENU-----------------------\n");
    printf("1.Add\n");
    printf("2.Remove\n");
    printf("3.Display\n");
    printf("4.Search\n");
    printf("5.Exit\n");
    printf("---------------------------------MENU-----------------------\n");
}

void Menu(){
    while(1){
        int choice =0;
        char Name[40]="",Address[200]="",PhoneNo[10]="",City[30]="",State[30]="",Country[30]="";
        DisplayMenu();
        scanf("%d",&choice);
        printf("\n");
        switch(choice){
            case 1:
                printf("Addition of Record\n");
                printf("Enter Name: ");
                scanf("%s",Name);
                printf("Enter Address: ");
                scanf("%s",Address);
                printf("Enter PhoneNo: ");
                scanf("%s",PhoneNo);
                printf("Enter City: ");
                scanf("%s",City);
                printf("Enter State: ");
                scanf("%s",State);
                printf("Enter Country: ");
                scanf("%s",Country);
                Add(Name,Address,PhoneNo,City,State,Country);
                break;
            case 2:
                printf("Removal of Record\n");
                printf("Enter Name: ");
                scanf("%s",Name);
                Remove(Name);
                break;
            case 3:
                printf("Displaying Record\n");
                Display(0,maxValue);
                break;
            case 4:
                printf("Removal of Record\n");
                printf("Enter Name: ");
                scanf("%s",Name);
                printf("\n");
                Search(Name);
                break;
            case 5:
                printf("Exit\n");
                return;
            default:
                printf("Invalid Choice\n");
                break;
        }
    }
}

int main(){
    printf("\n--------------------WARNING-----------------------------\n");
    printf("        DO NOT USE CAPITAL LETTERS FOR ANY INPUT\n");
    printf("--------------------WARNING-----------------------------\n\n\n");
    

    Menu();
    return 0;
}


