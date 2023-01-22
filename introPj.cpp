

#include "stdio.h"
#include "stdlib.h"
#define SIZE 10000
struct Worker{
    int id;
    int age;
    char name[30];
    char email[50];
    char password[50];

};

struct Worker info[SIZE];

void gmailValidation(char userInputGmail[50]);
void printingAllData();
void login();
int charCounting(char toCount[50]);
void myStrCmp(char userInputChar[50]);
void passChecking(char pass[50] , int userIndex);
void recordingAllDataToFile();
void userActionSector();
void loadingAllDataFromFile();
void registration();
void lobby();

int eFound = -1;
int pFound=-1;
int tester=0;
int globalIndex=0;

int main(){


    loadingAllDataFromFile();
    printingAllData();
    lobby();


    return 0;
}
void lobby(){
    int lob=0;
    printf("This is Lobby Sector!\n");
    printf("Press 1 to Register:\n");
    printf("Press 2 to Login:\n");
    printf("Press 3 to Exit:");

    scanf(" %d",&lob);

    if(lob == 1){
        registration();

    } else if(lob == 2){

        login();
    } else if(lob == 3){
        recordingAllDataToFile();
        exit(1);
    } else{
        printf("Invalid Option!\n");
        lobby();
    }


}

void printingAllData(){

    for(int gcc=0; gcc< globalIndex ; gcc++ ){

        printf("id: %d-name:%s - age:%d - email:%s - password:%s\n",info[gcc].id,info[gcc].name , info[gcc].age , info[gcc].email , info[gcc].password);

    }
}

void login(){
    char lEmail[50];
    char passWord[50];
    int found  = -1;
    printf("This is login form:\n");

    printf("Enter your email to login:");
    scanf(" %[^\n]",&lEmail);

    eFound = -1;
    myStrCmp(lEmail);

    printf("Enter your password :");
    scanf(" %[^\n]",&passWord);

    pFound = -1;
    passChecking(passWord , eFound);


    if(eFound != -1 && pFound == 1){
        userActionSector();


    } else{
        printf("Invalid email: or Password \n");
        login();
    }

}

void myStrCmp(char userInputChar[50]){

    int sameCount=0;
    int sec = charCounting(userInputChar);

    for(int i=0; i<globalIndex ; i++){
        int first = charCounting(info[i].email);

        if( first == sec){

            for(int gcc=0; gcc<first ; gcc++){

                if( info[i].email[gcc] != userInputChar[gcc]){

                    break;
                } else{
                    sameCount++;

                }

            }

        }
        if( sec == sameCount){
            eFound = i;
            break;
        }

    }

}

void passChecking(char pass[50] , int userIndex){

    int passCount = charCounting(pass);
    int infoPassCount = charCounting(info[userIndex].password);

    int sameCount=0;

    if(passCount == infoPassCount) {

        for (int ncc = 0; ncc < passCount; ncc++) {

            if (pass[ncc] == info[userIndex].password[ncc]) {

                sameCount++;

            } else{
                break;
            }


        }

        if( sameCount == passCount){
            pFound = 1;
        }
    }

}

int charCounting(char toCount[50]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void recordingAllDataToFile(){

    FILE *fptr = fopen("dipDB.txt","w");

    if(fptr == NULL){
        printf("Error at recordingAllDataToFile fun():\n");
    } else{

        for(int gcc=0; gcc<globalIndex; gcc++){


            fprintf(fptr , "%d %d %s %s %s\n",info[gcc].id , info[gcc].age , info[gcc].name , info[gcc].email  , info[gcc].password);


        }
        printf("Recording all data to dipDB.txt is complete!\n");
    }

    fclose(fptr);

}

void userActionSector(){

    int userAction=0;

    printf("Welcome Sir: %s\n",info[eFound].name);
    printf("Press 1 to User Action Sector:\n");
    printf("Press 2 to Home:\n");
    printf("Press 3 to Exit:");
    scanf(" %d",&userAction);

    if(userAction == 1){
        printf("this is user action sector:\n");
    } else if( userAction == 2){
        login();
    } else if(userAction == 3){
        recordingAllDataToFile();
    } else{
        printf("Invalid Option!\n");
        userActionSector();
    }
}

void loadingAllDataFromFile(){

    FILE *fptr = fopen("dipDB.txt","r");

    if(fptr == NULL){
        printf("Error at loading!\n");
    } else{

        for(int gcc=0; gcc<SIZE ; gcc++){

            fscanf(fptr ,"%d%d%s%s%s",&info[gcc].id , &info[gcc].age, &info[gcc].name,&info[gcc].email,&info[gcc].password);

            if(info[gcc].name[0] == '\0'){
                break;
            }
            globalIndex++;

        }

    }


}

void registration(){

    printf("This is registration\n");

    info[globalIndex].id=globalIndex+1;

    printf("Enter your name\n");
    scanf(" %[^\n]",&info[globalIndex].name);

    printf("Enter your Email\n");
    scanf(" %[^\n]",&info[globalIndex].email);

    //Gmail validation
    tester=0;
    gmailValidation(info[globalIndex].email);
    if(tester==1){
        eFound=-1;
        myStrCmp(info[globalIndex].email);

        if(eFound==-1){
            printf("You can register\n");
        }else{
            printf("Your Gmail is already existed, Try another one!\n");
        }

    } else{
        printf("Your Gmail is invalid! Pls Try Again\n");
        registration();
    }

    printf("Enter your Age\n");
    scanf("%d",&info[globalIndex].age);

    printf("Enter your password\n");
    scanf(" %[^\n]",&info[globalIndex].password);

    globalIndex++; //for new user

    recordingAllDataToFile();
    printf("Registration Complete");

}

void gmailValidation(char userInputGmail[50]){

    char gmailTemp[10]={'@','g','m','a','i','l','.','c','o','m'};
    int userGmail= charCounting(userInputGmail);
    int index=0;
    int count=0;
    int testing=0;
    int varPlus=0;
    for(int i=0;i<userGmail;i++){
        if(userInputGmail[i]=='@') {
            break;
        }
        index=i;
    }

    for(int i=index;i<userGmail;i++){
        if(userInputGmail[i]==gmailTemp[varPlus]){
            if(userInputGmail[i]=='\0'){
                break;
            }
            varPlus++;
            testing++;
        }

    }

    if(testing==10){
        tester=1;
    }else{
        tester=-1;
    }

}