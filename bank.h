#include "avl.h"
#include<time.h>

struct Date{
    char day[5];
    char month[5];
    char year[5];
};

typedef struct Date Date;

void main_sector();
void login_sector();
void register_sector();
void user_sector(Node* userNode);
void user_transfer_money(Node* userNode);
void continue_to_transfer(Node* userNode);
void transfer_money_record(Node* userNode, Node* receiverNode, char who, unsigned int amount);
void user_cash_in_out(Node* userNode);
void user_cash_in(Node* userNode);
void cash_in_record(Node* userNode, unsigned int amount);
void user_cash_out(Node* userNode);
void cash_out_record(Node* userNode, unsigned int amount);
void user_profile(Node* userNode);
void profile_update_record(Node* userNode);
void user_loan(Node* userNode);
void loan_take(Node* userNode);
void loan_take_record(Node* userNode, unsigned int amount);
void loan_payment(Node* userNode);
void loan_payment_record(Node* userNode, unsigned int amount);
void user_history(Node* userNode);
void all_history(Node* userNode);
void transfer_money_history(Node* userNode);
void cash_in_out_history(Node* userNode);
void profile_update_history(Node* userNode);
void loan_history(Node* userNode);

//amount limit per day
Date get_current_date();
Date get_date_from_record(char note[]);
unsigned int get_total_amount_of_same_day(Node* userNode);
unsigned int get_amount_from_record(char note[]);

Node* searchNodeByEmail(Node* node, char email[]);
Node* check_email_exists(Node* node, char email[]);
Node* searchNodeById(Node* node, int id);
Node* check_id_exists(Node* node, int id);
Node* searchNodeByNRC(Node* node, char nrc[]);
Node* check_nrc_exists(Node* node, char nrc[]);
void write_data_to_file(Node* node, FILE *fptr);
void recording_all_data_to_file(Node* node);
void loading_all_data_from_file();
int count_lines_from_file();

void get_time();
struct my_time{
    char c_time[25];
};
struct my_time Ctime[1];

void main_sector()
{
    printInOrder(root);
    char input[10];
    int option = 0;
    printf("\nZ Bank\n******\n");
    printf("1. Login\n2. Register\n0. Exit\n");
    printf("Enter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);

    switch(option){
        case 49:
            login_sector();
            break;
        case 50:
            register_sector();
            break;
        case 48:
            recording_all_data_to_file(root);
            printf("Exit...\n");
            exit(0);
        default:
            printf("Invalid Option! Try Again!\n");
            main_sector();
    }

}

void login_sector()
{
    char input[10];
    int option = 0;
    int l_id = 0;
    char l_email[50];
    char l_password[50];
    printf("Login Sector\n************\n");
    printf("1. Login with email\n2. Login with id\n0. Back to main sector\nEnter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);

    if(option == 49){
        printf("Enter your email to login : ");
        scanf(" %[^\n]", l_email);
        if(is_valid_email(l_email)){
            Node* userNode = check_email_exists(root, l_email);
            if(userNode != NULL){
                printf("Enter your password to login : ");
                scanf(" %[^\n]", l_password);
                if(string_compare(userNode->data.password, l_password) == 0){
                    user_sector(userNode);
                }else{
                    printf("Login Credential Wrong! Try again!\n");
                    login_sector();
                }
            }else{
                printf("Email not found! Please register first!\n");
                main_sector();
            }
        }else{
            printf("Invalid format! Try again!\n");
            login_sector();
        }
    }else if(option == 50){
        printf("Enter your id to login : ");
        scanf("%d", &l_id);
        Node* userNode = check_id_exists(root, l_id);
        if(userNode != NULL){
            printf("Enter your password to login : ");
            scanf(" %[^\n]", l_password);
            if(string_compare(userNode->data.password, l_password) == 0){
                user_sector(userNode);
            }else{
                printf("Login Credential Wrong! Try again!\n");
                login_sector();
            }
        }else{
            printf("ID not found! Please register first!\n");
            main_sector();
        }
    }else if(option == 48){
        main_sector();
    }else{
        printf("Invalid option! Try again!\n");
        login_sector();
    }

}

void register_sector()
{
    char r_email[50];
    char r_name[50];
    char r_phone[15];
    char r_password[50];
    char r_nrc[25];
    char r_address[50];
    char r_accountType[10];
    unsigned int r_monthlyIncome = 0;
    unsigned int r_loanAmount = 0;
    unsigned int r_curAmount = 0;
    unsigned int r_walletCapacity = 0;
    unsigned int r_amountLimitPerDay = 0;

    //email, name, password, address
    for(int i = 0; i<50; i++){
        r_email[i] = '\0';
        r_name[i] = '\0';
        r_password[i] = '\0';
        r_address[i] = '\0';
    }

    printf("\nRegister Sector\n***************\n");
    printf("Enter your email to register : ");
    scanf(" %[^\n]", r_email);
    if(is_valid_email(r_email)){
        if(check_email_exists(root, r_email) == NULL){
            
            while(!is_space(r_name)){
                printf("Enter your name to register : ");
                scanf(" %[^\n]", r_name);
                if(!is_space(r_name)){
                    printf("Name can't contain white space!\n");
                }
            }
            
            while(!is_phone_valid(r_phone)){
                printf("Enter your phone number to register : ");
                scanf(" %[^\n]", r_phone);
                if(!is_phone_valid(r_phone)){
                    printf("Invalid format! Format must be - 959xxxxxxxxx\n");
                }
            }
            while(!is_strong_password(r_password)){
                printf("Enter your password to register : ");
                scanf(" %[^\n]", r_password);
                if(!is_strong_password(r_password)){
                    printf("Weak password! Password must contains upper case, lower case, number, special character!\n");
                }
            }

            while(!is_NRC_valid(r_nrc)){
                printf("Enter your nrc to register : ");
                scanf(" %[^\n]", r_nrc);
                if(check_nrc_exists(root, r_nrc) == NULL){
                    if(!is_NRC_valid(r_nrc)){
                        printf("Invalid Format! Only support Yangon NRC!\n");
                    }
                }else{
                    string_copy(r_nrc, "random");
                    printf("NRC already exists! Try again!\n");
                }
                
            }

            while(!is_accountType_valid(r_accountType)){
                printf("Enter your account type to register : ");
                scanf(" %[^\n]", r_accountType);
                if(!is_accountType_valid(r_accountType)){
                    printf("Account type must be Personal or Business! Try again!\n");
                }
            }
            printf("Enter your monthly income to register : ");
            scanf("%u", &r_monthlyIncome);

            while(!is_space(r_address)){
                printf("Enter your address to register : ");
                scanf(" %[^\n]", r_address);
                if(!is_space(r_address)){
                    printf("Address can't contain white space!\n");
                }
            }

            r_loanAmount = 0;
            r_curAmount = 0;
            if(string_compare(r_accountType, "Personal") == 0){
                r_walletCapacity = 1000000;
                r_amountLimitPerDay = 500000;
            }else{
                r_walletCapacity = 10000000;
                r_amountLimitPerDay = 5000000;
            }

            Data data;
            data.id = count_node(root) + 1001;
            string_copy(data.name, r_name);
            string_copy(data.phone, r_phone);
            string_copy(data.email, r_email);
            string_copy(data.password, r_password);
            string_copy(data.nrc, r_nrc);
            string_copy(data.address, r_address);
            string_copy(data.account_type, r_accountType);
            data.monthly_income = r_monthlyIncome;
            data.loan_amount = r_loanAmount;
            data.cur_amount = r_curAmount;
            data.wallet_capacity = r_walletCapacity;
            data.amount_limit_per_day = r_amountLimitPerDay;
            space_array[data.id - 1001] = 12;
            root = insertNode(root, data);

            printf("Registration Success!\n");
            main_sector();

        }else{
            printf("Your email have already in use!\n");
            main_sector();
        }
    }else{
        printf("Invalid Format! It support only gmail!\n");
        register_sector();
    }
}

Node* searchNodeByEmail(Node* node, char email[])
{
    if(node == NULL || string_compare(node->data.email, email) == 0){
        return node;
    }

    if(string_compare(node->data.email, email) > 0){
        return searchNodeByEmail(node->left, email);
    }else{
        return searchNodeByEmail(node->right, email);
    }

}

Node* check_email_exists(Node* node, char email[])
{
    Node* resultNode = searchNodeByEmail(node, email);
    if(resultNode != NULL){
        return resultNode;
    }else{
        return NULL;
    }
}

Node* searchNodeById(Node* node, int id)
{
    if(node == NULL || node->data.id == id){
        return node;
    }
    if(node->data.id > id){
        return searchNodeById(node->left, id);
    }else{
        return searchNodeById(node->right, id);
    }
}

Node* check_id_exists(Node* node, int id)
{
    Node* resultNode = searchNodeById(node, id);
    if(resultNode != NULL){
        return resultNode;
    }else{
        return NULL;
    }
}

Node* searchNodeByNRC(Node* node, char nrc[])
{
    if(node == NULL || string_compare(node->data.nrc, nrc) == 0){
        return node;
    }

    if(string_compare(node->data.nrc, nrc) > 0){
        return searchNodeByNRC(node->left, nrc);
    }else{
        return searchNodeByNRC(node->right, nrc);
    }
}

Node* check_nrc_exists(Node* node, char nrc[])
{
    Node* resultNode = searchNodeByNRC(node, nrc);
    if(resultNode != NULL){
        return resultNode;
    }else{
        return NULL;
    }
}

void user_sector(Node* userNode)
{
    char input[10];
    int option = 0;
    printf("\nUser Sector\n***********\n");
    printf("Welcome %s! Your current amount is %u\n\n", userNode->data.name, userNode->data.cur_amount);
    printf("1. Transfer Money\n2. Cash in/Cash Out\n3. Profile\n4. Loan\n5. History\n0. Logout\nEnter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 49){
        user_transfer_money(userNode);
    }else if(option == 50){
        user_cash_in_out(userNode);
    }else if(option == 51){
        user_profile(userNode);
    }else if(option == 52){
        user_loan(userNode);
    }else if(option == 53){
        user_history(userNode);
    }else if(option == 48){
        printf("Logout from %d account!\n", userNode->data.id);
        main_sector();
    }else{
        printf("Invalid Option! Try again!\n");
        user_sector(userNode);
    }

}

void write_data_to_file(Node* node, FILE *fptr)
{
    if(node != NULL){
        write_data_to_file(node->left, fptr);

        fprintf(fptr, "%d %s %s %s %s %s %s %s %u %u %u %u %u", node->data.id, node->data.name, node->data.phone, node->data.email, node->data.password, node->data.nrc, node->data.address, node->data.account_type, node->data.monthly_income, node->data.loan_amount, node->data.cur_amount, node->data.wallet_capacity, node->data.amount_limit_per_day);

        for(int i = 0; i<(space_array[node->data.id - 1001] - 12); i++){
            // printf(" %s", node->data.hist[i].note);
            fprintf(fptr, " %s", node->data.hist[i].note);
        }

        fprintf(fptr, "%c", '\n');

        write_data_to_file(node->right, fptr);
    }
}

void recording_all_data_to_file(Node* node)
{
    FILE *fptr;
    fptr = fopen("zdb.txt", "w");
    if(fptr == NULL){
        printf("Error: recording data to file!\n");
        exit(1);
    }else{
        write_data_to_file(node, fptr);
    }
    fclose(fptr);
}

void loading_all_data_from_file()
{
    FILE *fptr;
    fptr = fopen("zdb.txt", "r");
    if(fptr == NULL){
        printf("Error: loading data from file!\n");
        exit(1);
    }else{
        for(int i = 0; i<count_lines_from_file(); i++){
            int id = 0;
            char name[50];
            char phone[15];
            char email[50];
            char password[50];
            char nrc[25];
            char address[50];
            char account_type[10];
            unsigned int monthly_income = 0;
            unsigned int loan_amount = 0;
            unsigned int cur_amount = 0;
            unsigned int wallet_capacity = 0;
            unsigned int amount_limit_per_day = 0;
            char note[100][100];
            fscanf(fptr, "%d %s %s %s %s %s %s %s %u %u %u %u %u", &id, name, phone, email, password, nrc, address, account_type, &monthly_income, &loan_amount, &cur_amount, &wallet_capacity, &amount_limit_per_day);


            for(int j = 0; j<space_array[i] - 12; j++){
                fscanf(fptr, " %s", note[j]);
            }

            Data data;
            data.id = id;
            string_copy(data.name, name);
            string_copy(data.phone, phone);
            string_copy(data.email, email);
            string_copy(data.password, password);
            string_copy(data.nrc, nrc);
            string_copy(data.address, address);
            string_copy(data.account_type, account_type);
            data.monthly_income = monthly_income;
            data.loan_amount = loan_amount;
            data.cur_amount = cur_amount;
            data.wallet_capacity = wallet_capacity;
            data.amount_limit_per_day = amount_limit_per_day;

            for(int j = 0; j<space_array[i] - 12; j++){
                string_copy(data.hist[j].note, note[j]);
            }

            root = insertNode(root, data);
        }
    }
    fclose(fptr);
}

int count_lines_from_file()
{
    FILE *fptr;
    int count = 0;
    fptr = fopen("zdb.txt", "r");
    if(fptr == NULL){
        printf("Error: count lines from file!\n");
        exit(1);
    }else{
        char c;
        c = fgetc(fptr);
        while (c != EOF)
        {
            if(c == '\n'){
                count++;
            }
            c = fgetc(fptr);
        }
        
    }  
    fclose(fptr);
    return count;
}

void user_transfer_money(Node* userNode)
{
    char input[10];
    int option = 0;
    printf("\nTransfer Money\n**************\n");
    printf("Your current amount is %u\n\n", userNode->data.cur_amount);
    printf("1. Continue to transfer\n0. Back to user sector\nEnter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 49){
        continue_to_transfer(userNode);
    }else if(option == 48){
        user_sector(userNode);
    }else{
        printf("Invalid Option! Try again!\n");
        user_transfer_money(userNode);
    }
}

void continue_to_transfer(Node* userNode)
{
    char input[10];
    int option = 0;
    unsigned int amountToTransfer = 0;
    unsigned int totalReceiveAmount = 0;
    char passwordToConfirm[50];
    Node* receiverNode = NULL;
    char yOrn;

    printf("Your current amount is %u\n", userNode->data.cur_amount);
    printf("1. Transfer with ID number\n2. Transfer with Email\n");
    printf("Enter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);

    if(option == 49){
        //transfer with id
        int id = 0;
        receiverNode = check_id_exists(root, id);
        while(receiverNode == NULL){
            printf("Enter receiver ID : ");
            scanf("%d", &id);
            receiverNode = check_id_exists(root, id);
            if(receiverNode == NULL){
                printf("Bank user does not exist with that ID!\n");
            }
        }

    }else if(option == 50){
        //transfer with email
        char email[50];
        receiverNode = check_email_exists(root, email);
        while(receiverNode == NULL){
            printf("Enter receiver email : ");
            scanf(" %[^\n]", email);
            receiverNode = check_email_exists(root, email);
            if(receiverNode == NULL){
                printf("Bank user does not exist with that email!\n");
            }
        }
    }else{
        printf("Invalid option! Try again!\n");
        continue_to_transfer(userNode);
    }
    printf("Receiver info : %d - %s - %s\n", receiverNode->data.id, receiverNode->data.name, receiverNode->data.email);

    printf("Are you sure to transfer to this user(y/n)? :-> ");
    scanf(" %c", &yOrn);
    if(yOrn == 'y' || yOrn == 'Y'){
        while(amountToTransfer < userNode->data.cur_amount){
            printf("Enter your amount to transfer : ");
            scanf("%u", &amountToTransfer);

            if(userNode->data.cur_amount > amountToTransfer){
                totalReceiveAmount = amountToTransfer + receiverNode->data.cur_amount;

                if(totalReceiveAmount > receiverNode->data.wallet_capacity){
                    printf("Receiver wallet capacity was exceeded! You can transfer at most %d\n", receiverNode->data.wallet_capacity - receiverNode->data.cur_amount);
                    amountToTransfer = 0;
                }else{
                    //check amount limit per day here
                    unsigned int total_amount_of_same_day_for_user = get_total_amount_of_same_day(userNode);
                    unsigned int total_amount_of_same_day_for_receiver = get_total_amount_of_same_day(receiverNode);
                    //check current user
                    if((total_amount_of_same_day_for_user + amountToTransfer) > userNode->data.amount_limit_per_day){
                        unsigned int transfer_at_most = userNode->data.amount_limit_per_day - total_amount_of_same_day_for_user;
                        printf("Your amount limit per day was exceeded! You can transfer at most %u toady\n", transfer_at_most);
                        amountToTransfer = 0;
                    }else{
                        //check receiver
                        if((total_amount_of_same_day_for_receiver + amountToTransfer) > receiverNode->data.amount_limit_per_day){
                            unsigned int receive_at_most = receiverNode->data.amount_limit_per_day - total_amount_of_same_day_for_receiver;
                            printf("Receiver amount limit per day was exceeded! Receiver can receive at most %u today\n", receive_at_most);
                            amountToTransfer = 0;
                        }else{
                            break;
                        }
                    }

                }

            }else{
                printf("Your current amount is not enough to transfer!\n");
                amountToTransfer = 0;
            }

        }

        while(string_compare(userNode->data.password, passwordToConfirm) != 0){
            printf("Enter your password to confirm transfer money : ");
            scanf(" %[^\n]", passwordToConfirm);
            if(string_compare(userNode->data.password, passwordToConfirm) != 0){
                printf("Incorret Password! Try again!\n");
            }
        }

        printf("Transfer money to %s complete!\n", receiverNode->data.name);
        // receiverNode->data.cur_amount += amountToTransfer;
        transfer_money_record(userNode, receiverNode, 't', amountToTransfer);
        transfer_money_record(userNode, receiverNode, 'r', amountToTransfer);
        user_sector(userNode);

    }else{
        user_transfer_money(userNode);
    }

}

void transfer_money_record(Node* userNode, Node* receiverNode, char who, unsigned int amount)
{
    // t for transferer | r for receiver
    int user_sa_index = userNode->data.id - 1001;
    int receiver_sa_index = receiverNode->data.id - 1001;
    int user_name_counter = string_length(userNode->data.name);
    int receiver_name_counter = string_length(receiverNode->data.name);
    char char_amount[20];
    for(int i = 0; i<20; i++){
        char_amount[i] = '\0';
    }
    sprintf(char_amount, "%u", amount);

    if(who == 't'){
        //transferer record
        int index_counter = 0;
        char transferer_note[100];
        for(int i = 0; i<100; i++){
            transferer_note[i] = '\0';
        }

        char first_text[] = "1_Send_Money_To_";
        int first_text_counter = string_length(first_text);
        for(int i = 0; i<first_text_counter; i++){
            transferer_note[index_counter] = first_text[i];
            index_counter++;
        }

        for(int i = 0; i<receiver_name_counter; i++){
            transferer_note[index_counter] = receiverNode->data.name[i];
            index_counter++;
        }

        char second_text[] = "_$";
        int second_text_counter = string_length(second_text);
        for(int i = 0; i<second_text_counter; i++){
            transferer_note[index_counter] = second_text[i];
            index_counter++;
        }

        int char_amount_counter = string_length(char_amount);
        for(int i = 0; i<char_amount_counter; i++){
            transferer_note[index_counter] = char_amount[i];
            index_counter++;
        }

        char third_text[] = "_at";
        int third_text_counter = string_length(third_text);
        for(int i = 0; i<third_text_counter; i++){
            transferer_note[index_counter] = third_text[i];
            index_counter++;
        }

        get_time();
        for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
            transferer_note[index_counter] = Ctime[0].c_time[i];
            index_counter++;
        }

        string_copy(userNode->data.hist[space_array[user_sa_index]-12].note, transferer_note);

        space_array[userNode->data.id - 1001]++;
        userNode->data.cur_amount -= amount;

    }else{
        //transferer record
        int index_counter = 0;
        char receiver_note[100];
        for(int i = 0; i<100; i++){
            receiver_note[i] = '\0';
        }

        char first_text[] = "1_Receive_Money_From_";
        int first_text_counter = string_length(first_text);
        for(int i = 0; i<first_text_counter; i++){
            receiver_note[index_counter] = first_text[i];
            index_counter++;
        }

        for(int i = 0; i<user_name_counter; i++){
            receiver_note[index_counter] = userNode->data.name[i];
            index_counter++;
        }

        char second_text[] = "_$";
        int second_text_counter = string_length(second_text);
        for(int i = 0; i<second_text_counter; i++){
            receiver_note[index_counter] = second_text[i];
            index_counter++;
        }

        int char_amount_counter = string_length(char_amount);
        for(int i = 0; i<char_amount_counter; i++){
            receiver_note[index_counter] = char_amount[i];
            index_counter++;
        }

        char third_text[] = "_at";
        int third_text_counter = string_length(third_text);
        for(int i = 0; i<third_text_counter; i++){
            receiver_note[index_counter] = third_text[i];
            index_counter++;
        }

        get_time();
        for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
            receiver_note[index_counter] = Ctime[0].c_time[i];
            index_counter++;
        }

        string_copy(receiverNode->data.hist[space_array[receiver_sa_index]-12].note, receiver_note);

        space_array[receiverNode->data.id - 1001]++;
        receiverNode->data.cur_amount += amount;

        
    }

}

void user_cash_in_out(Node* userNode)
{
    char input[10];
    int option = 0;
    printf("\nCash in/Cash out\n****************\n");
    printf("Your current amount is %u\n", userNode->data.cur_amount);
    printf("1. Cash in\n2. Cash out\n0. Back to user sector\nEnter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 49){
        user_cash_in(userNode);
    }else if(option == 50){
        user_cash_out(userNode);
    }else if(option == 48){
        user_sector(userNode);
    }else{
        printf("Invalid option! Try again!\n");
        user_cash_in_out(userNode);
    }
}

void user_cash_in(Node* userNode)
{
    unsigned int cashInAmount = 0;
    printf("Enter your amount to cash in : ");
    scanf("%u", &cashInAmount);
    unsigned int totalAmount = cashInAmount + userNode->data.cur_amount;
    if(totalAmount > userNode->data.wallet_capacity){
        printf("Your wallet capacity was exceeded! You can cash in at most %u\n", userNode->data.wallet_capacity - userNode->data.cur_amount);
        user_cash_in_out(userNode);
    }else{
        unsigned total_amount_for_same_day = get_total_amount_of_same_day(userNode);
        if((cashInAmount + total_amount_for_same_day) > userNode->data.amount_limit_per_day){
            unsigned int at_most_cash_in = userNode->data.amount_limit_per_day - total_amount_for_same_day;
            printf("Your amount limit per day was exceeded! You can cash in at most %u today!\n", at_most_cash_in);
            user_cash_in_out(userNode);
        }else{
            userNode->data.cur_amount = totalAmount;
            cash_in_record(userNode, cashInAmount);
            printf("Cash in success!\n");
            user_sector(userNode);
        }
    }
    
}

void cash_in_record(Node* userNode, unsigned int amount)
{
    int index_counter = 0;
    int user_index = userNode->data.id - 1001;
    char char_amount[20];
    for(int i = 0; i<20; i++){
        char_amount[i] = '\0';
    }
    sprintf(char_amount, "%u", amount);
    char cash_in_note[100];
    for(int i = 0; i<100; i++){
        cash_in_note[i] = '\0';
    }

    char first_text[] = "2_Cash_In_$";
    int first_text_counter = string_length(first_text);
    for(int i = 0; i<first_text_counter; i++){
        cash_in_note[index_counter] = first_text[i];
        index_counter++;
    }

    int char_amount_counter = string_length(char_amount);
    for(int i = 0; i<char_amount_counter; i++){
        cash_in_note[index_counter] = char_amount[i];
        index_counter++;
    }

    char second_text[] = "_at";
    int second_text_counter = string_length(second_text);
    for(int i = 0; i<second_text_counter; i++){
        cash_in_note[index_counter] = second_text[i];
        index_counter++;
    }

    get_time();
    for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
        cash_in_note[index_counter] = Ctime[0].c_time[i];
        index_counter++;
    }

    string_copy(userNode->data.hist[space_array[user_index]-12].note, cash_in_note);

    space_array[userNode->data.id - 1001]++;

}   

void user_cash_out(Node* userNode)
{
    unsigned int cashOutAmount = 0;
    printf("Enter your amount to cash out : ");
    scanf("%u", &cashOutAmount);
    if(cashOutAmount > userNode->data.cur_amount){
        printf("No enough balance to cash out! You can cash out at most $%u", userNode->data.cur_amount);
        user_cash_in_out(userNode);
    }else{
        unsigned total_amount_for_same_day = get_total_amount_of_same_day(userNode);
        if((cashOutAmount + total_amount_for_same_day) > userNode->data.amount_limit_per_day){
            unsigned int at_most_cash_in = userNode->data.amount_limit_per_day - total_amount_for_same_day;
            printf("Your amount limit per day was exceeded! You can cash out at most %u today!\n", at_most_cash_in);
            user_cash_in_out(userNode);
        }else{
            userNode->data.cur_amount -= cashOutAmount;
            cash_out_record(userNode, cashOutAmount);
            printf("Cash out success!\n");
            user_sector(userNode);
        }
    }
}

void cash_out_record(Node* userNode, unsigned int amount)
{
    int index_counter = 0;
    int user_index = userNode->data.id - 1001;
    char char_amount[20];
    for(int i = 0; i<20; i++){
        char_amount[i] = '\0';
    }
    sprintf(char_amount, "%u", amount);
    char cash_in_note[100];
    for(int i = 0; i<100; i++){
        cash_in_note[i] = '\0';
    }

    char first_text[] = "2_Cash_Out_$";
    int first_text_counter = string_length(first_text);
    for(int i = 0; i<first_text_counter; i++){
        cash_in_note[index_counter] = first_text[i];
        index_counter++;
    }

    int char_amount_counter = string_length(char_amount);
    for(int i = 0; i<char_amount_counter; i++){
        cash_in_note[index_counter] = char_amount[i];
        index_counter++;
    }

    char second_text[] = "_at";
    int second_text_counter = string_length(second_text);
    for(int i = 0; i<second_text_counter; i++){
        cash_in_note[index_counter] = second_text[i];
        index_counter++;
    }

    get_time();
    for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
        cash_in_note[index_counter] = Ctime[0].c_time[i];
        index_counter++;
    }

    string_copy(userNode->data.hist[space_array[user_index]-12].note, cash_in_note);

    space_array[userNode->data.id - 1001]++;
}

void user_profile(Node* userNode)
{
    char input[10];
    int option = 0;

    printf("\nUser Profile\n************\n");
    printf("ID : %d\n", userNode->data.id);
    printf("Name : %s\n", userNode->data.name);
    printf("Phone : %s\n", userNode->data.phone);
    printf("Email : %s\n", userNode->data.email);
    printf("Password : %s\n", userNode->data.password);
    printf("NRC : %s\n", userNode->data.nrc);
    printf("Address : %s\n", userNode->data.address);
    printf("Account Type : %s\n", userNode->data.account_type);
    printf("Monthly income : %u\n", userNode->data.monthly_income);
    printf("Loan Amount : %u\n", userNode->data.loan_amount);
    printf("Current Amount : %u\n", userNode->data.cur_amount);
    printf("Wallet Capacity : %u\n", userNode->data.wallet_capacity);
    printf("Amount limit per day : %u\n", userNode->data.amount_limit_per_day);

    if(string_compare(userNode->data.account_type, "Personal") == 0){
        printf("1. Update user account type\n");
    }
    printf("0. Back to main sector\n");
    printf("Enter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);

    if(option == 49){
        if(string_compare(userNode->data.account_type, "Personal") == 0){
            string_copy(userNode->data.account_type, "Business");
            userNode->data.wallet_capacity = 10000000;
            userNode->data.amount_limit_per_day = 5000000;
            printf("Account type updated success!\n");
            profile_update_record(userNode);
            user_profile(userNode);
        }else{
            printf("Invalid option! Try again!\n");
            user_profile(userNode);
        }
    }else if(option == 48){
        user_sector(userNode);
    }else{
        printf("Invalid option! Try again!\n");
        user_profile(userNode);
    }

}

void profile_update_record(Node* userNode)
{
    int index_counter = 0;
    int user_index = userNode->data.id - 1001;
    char update_note[100];
    for(int i = 0; i<100; i++){
        update_note[i] = '\0';
    }

    char first_text[] = "3_Account_type_updated";
    int first_text_counter = string_length(first_text);
    for(int i = 0; i<first_text_counter; i++){
        update_note[index_counter] = first_text[i];
        index_counter++;
    }

    char second_text[] = "_at";
    int second_text_counter = string_length(second_text);
    for(int i = 0; i<second_text_counter; i++){
        update_note[index_counter] = second_text[i];
        index_counter++;
    }

    get_time();
    for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
        update_note[index_counter] = Ctime[0].c_time[i];
        index_counter++;
    }

    string_copy(userNode->data.hist[space_array[user_index]-12].note, update_note);

    space_array[userNode->data.id - 1001]++;
}

void user_loan(Node* userNode)
{
    char input[10];
    int option = 0;
    printf("Loan Page\n*********\n");
    printf("Your current amount is %u! Your monthly income is %u!\n", userNode->data.cur_amount, userNode->data.monthly_income);
    printf("The Interest rate at a time is 10% . You can make loan payment within 3 months\n");
    printf("Loan payment is one time payment! You must pay the (loan + interest) at a time.\n");
    printf("Your loan amount to take at most is 3 times of your monthly income!\n");
    printf("1. Take a loan\n");
    if(userNode->data.loan_amount != 0){
        printf("2. Loan Payment\n");
    }
    printf("0. Back to user sector\n");
    printf("Enter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 49){
        //take a loan
        loan_take(userNode);
    }else if(option == 50){
        //loan payment
        if(userNode->data.loan_amount != 0){
            loan_payment(userNode);
        }else{
            printf("Invalid option! Try again!\n");
            user_loan(userNode);
        }
    }else if(option == 48){
        user_sector(userNode);
    }else{
        printf("Invalid option! Try again!\n");
        user_loan(userNode);
    }
    
}

void loan_take(Node* userNode)
{
    unsigned int loan_amount = 0;
    printf("Enter your loan amount : ");
    scanf("%u", &loan_amount);
    //loan amount check
    if(loan_amount <= (userNode->data.monthly_income * 3)){
        //check wallet capacity
        unsigned int total_amount = 0;
        total_amount = loan_amount + userNode->data.cur_amount;
        if(total_amount <= userNode->data.wallet_capacity){
            
            unsigned int total_amount_for_same_day = get_total_amount_of_same_day(userNode);
            if((total_amount_for_same_day + loan_amount) > userNode->data.amount_limit_per_day){
                unsigned int loan_at_most = userNode->data.amount_limit_per_day - total_amount_for_same_day;
                printf("Your amount limit per day was exceeded! You can loan at most %u today!\n", loan_at_most);
                user_loan(userNode);
            }else{
                unsigned int loan_pay_amount = 0;
                userNode->data.cur_amount += loan_amount;
                userNode->data.loan_amount = loan_amount;
                loan_pay_amount = loan_amount + (0.1*loan_amount);
                loan_take_record(userNode, loan_amount);
                printf("Taking loan success!\n");
                printf("When you pay the loan, you must pay (loan amount + 10%) %u!\n", loan_pay_amount);
                user_loan(userNode);
            }
        }else{
            printf("Wallet capacity was exceeded!\n You can pay loan at most %u!\n", userNode->data.wallet_capacity - userNode->data.cur_amount);
            loan_take(userNode);
        }
    }else{
        printf("Too much amount! Try another amount!\n");
        printf("Loan amount to take at most is %u!\n", userNode->data.monthly_income * 3);
        loan_take(userNode);
    }
}

void loan_take_record(Node* userNode, unsigned int amount)
{
    char char_amount[20];
    for(int i = 0; i<20; i++){
        char_amount[i] = '\0';
    }
    sprintf(char_amount, "%u", amount);

    int index_counter = 0;
    int user_index = userNode->data.id - 1001;
    char loan_take_note[100];
    for(int i = 0; i<100; i++){
        loan_take_note[i] = '\0';
    }

    char first_text[] = "4_Loan_take_$";
    int first_text_counter = string_length(first_text);
    for(int i = 0; i<first_text_counter; i++){
        loan_take_note[index_counter] = first_text[i];
        index_counter++;
    }

    int char_amount_counter = string_length(char_amount);
    for(int i = 0; i<char_amount_counter; i++){
        loan_take_note[index_counter] = char_amount[i];
        index_counter++;
    }

    char second_text[] = "_at";
    int second_text_counter = string_length(second_text);
    for(int i = 0; i<second_text_counter; i++){
        loan_take_note[index_counter] = second_text[i];
        index_counter++;
    }

    get_time();
    for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
        loan_take_note[index_counter] = Ctime[0].c_time[i];
        index_counter++;
    }

    string_copy(userNode->data.hist[space_array[user_index]-12].note, loan_take_note);

    space_array[userNode->data.id - 1001]++;
}

void loan_payment(Node* userNode)
{
    unsigned int loan_to_pay = userNode->data.loan_amount + (userNode->data.loan_amount * 0.1);
    printf("You need to pay %u\n", (userNode->data.loan_amount * 0.1));
    if(userNode->data.cur_amount < loan_to_pay){
        printf("You don't have enough amount to pay the loan!");
        user_sector(userNode);
    }else{
        unsigned int total_amount_for_same_day = get_total_amount_of_same_day(userNode);
        if((total_amount_for_same_day + loan_to_pay) > userNode->data.amount_limit_per_day){
            unsigned int loan_at_most = userNode->data.amount_limit_per_day - total_amount_for_same_day;
            printf("Your amount limit per day was exceeded! You can pay loan at most %u today!\n", loan_at_most);
            user_loan(userNode);
        }else{
            userNode->data.loan_amount = 0;
            userNode->data.cur_amount -= loan_to_pay;
            loan_payment_record(userNode, loan_to_pay);
            printf("Loan payment success!\n");
            user_loan(userNode);
        }
        
    }
}

void loan_payment_record(Node* userNode, unsigned int amount)
{
    char char_amount[20];
    for(int i = 0; i<20; i++){
        char_amount[i] = '\0';
    }
    sprintf(char_amount, "%u", amount);

    int index_counter = 0;
    int user_index = userNode->data.id - 1001;
    char loan_pay_note[100];
    for(int i = 0; i<100; i++){
        loan_pay_note[i] = '\0';
    }

    char first_text[] = "4_Loan_pay_$";
    int first_text_counter = string_length(first_text);
    for(int i = 0; i<first_text_counter; i++){
        loan_pay_note[index_counter] = first_text[i];
        index_counter++;
    }

    int char_amount_counter = string_length(char_amount);
    for(int i = 0; i<char_amount_counter; i++){
        loan_pay_note[index_counter] = char_amount[i];
        index_counter++;
    }

    char second_text[] = "_at";
    int second_text_counter = string_length(second_text);
    for(int i = 0; i<second_text_counter; i++){
        loan_pay_note[index_counter] = second_text[i];
        index_counter++;
    }

    get_time();
    for(int i = 0; i<(string_length(Ctime[0].c_time)); i++){
        loan_pay_note[index_counter] = Ctime[0].c_time[i];
        index_counter++;
    }

    string_copy(userNode->data.hist[space_array[user_index]-12].note, loan_pay_note);

    space_array[userNode->data.id - 1001]++;
}

void user_history(Node* userNode)
{
    char input[10];
    int option = 0;
    printf("\nUser History\n************\n");
    printf("1. All history\n2. Transfer Money history\n3. Cash in/out history\n4. Profile update history\n5. Loan history\n0. Back to user sector\n");
    printf("Enter your option :-> ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 49){
        all_history(userNode);
    }else if(option == 50){
        transfer_money_history(userNode);
    }else if(option == 51){
        cash_in_out_history(userNode);
    }else if(option == 52){
        profile_update_history(userNode);
    }else if(option == 53){
        loan_history(userNode);
    }else if(option == 48){
        user_sector(userNode);
    }else{
        printf("Invalid option! Try again!\n");
    }
}

void all_history(Node* userNode)
{
    printf("\nAll history\n************\n");
    char input[10];
    int option = 0;
    int history_count = space_array[userNode->data.id - 1001] - 12;
    if(history_count == 0){
        printf("No history to show!\n");
    }else{
        for(int i = history_count-1; i>=0; i--){
            printf("%s\n", userNode->data.hist[i].note);
        }
    }
    
    printf("Enter 0 to continue : ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 48){
        user_history(userNode);
    }else{
        printf("Invalid input!\n");
        all_history(userNode);
    }
}

void transfer_money_history(Node* userNode)
{
    printf("\nTransfer Money history\n**********************\n");
    char input[10];
    int option = 0;
    int history_count = space_array[userNode->data.id - 1001] - 12;

    for(int i = history_count-1; i>=0; i--){
        if(userNode->data.hist[i].note[0] == '1'){
            printf("%s\n", userNode->data.hist[i].note);
        }
    }
    
    printf("Enter 0 to continue : ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 48){
        user_history(userNode);
    }else{
        printf("Invalid input!\n");
        all_history(userNode);
    }
}

void cash_in_out_history(Node* userNode)
{
    printf("\nCash in/out history\n*******************\n");
    char input[10];
    int option = 0;
    int history_count = space_array[userNode->data.id - 1001] - 12;

    for(int i = history_count-1; i>=0; i--){
        if(userNode->data.hist[i].note[0] == '2'){
            printf("%s\n", userNode->data.hist[i].note);
        }
    }
    
    printf("Enter 0 to continue : ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 48){
        user_history(userNode);
    }else{
        printf("Invalid input!\n");
        all_history(userNode);
    }
}

void profile_update_history(Node* userNode)
{
    printf("\nProfile Update history\n**********************\n");
    char input[10];
    int option = 0;
    int history_count = space_array[userNode->data.id - 1001] - 12;

    for(int i = history_count-1; i>=0; i--){
        if(userNode->data.hist[i].note[0] == '3'){
            printf("%s\n", userNode->data.hist[i].note);
        }
    }

    printf("Enter 0 to continue : ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 48){
        user_history(userNode);
    }else{
        printf("Invalid input!\n");
        all_history(userNode);
    }
}

void loan_history(Node* userNode)
{
    printf("\nLoan history\n************\n");
    char input[10];
    int option = 0;
    int history_count = space_array[userNode->data.id - 1001] - 12;

    for(int i = history_count-1; i>=0; i--){
        if(userNode->data.hist[i].note[0] == '4'){
            printf("%s\n", userNode->data.hist[i].note);
        }
    }

    printf("Enter 0 to continue : ");
    scanf(" %[^\n]", input);
    option = check_input(input);
    if(option == 48){
        user_history(userNode);
    }else{
        printf("Invalid input!\n");
        all_history(userNode);
    }
}

void space_counter(){
    FILE *fptr;
    fptr = fopen("zdb.txt", "r");
    if(fptr == NULL){
        printf("Error: Call Space Counter Function\n");
        exit(1);
    }else{
        char c = fgetc(fptr);
        int index = 0;
        while(!feof(fptr)){
            if(c != '\n'){
                if(c == ' '){
                    space_array[index]++;
                }
                c= fgetc(fptr);
            }else{
                index++;
                c = fgetc(fptr);
            }
        }

        for(int i = 0; i<100; i++){
            printf("%d ", space_array[i]);
        }
        printf("\n");

    }
    fclose(fptr);
}

void get_time(){
    time_t tm;
    time(&tm);

//    printf("Current time =%s\n", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));

    fclose(fptr);

    int index=0;
    int time_space_counter=0;

    Ctime[0].c_time[index]='_';
    index++;

    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while (c != '\n'){

        if( c==' '){

            time_space_counter++;

            if(time_space_counter == 1){
                Ctime[0].c_time[index]='!';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter == 2){
                Ctime[0].c_time[index]='#';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter==4){
                Ctime[0].c_time[index]='@';
                c = fgetc(fptr2);
                index++;
            } else{
                Ctime[0].c_time[index]='_';
                c = fgetc(fptr2);
                index++;
            }
        } else{

            Ctime[0].c_time[index]=c;
            c = fgetc(fptr2);
            index++;

        }
    }
}

Date get_current_date()
{
    get_time();
    char month[5];
    char day[5];
    char year[5];

    for(int i=0; i<5; i++){
        month[i] = '\0';
        day[i] = '\0';
        year[i] = '\0';
    }
    
    int time_counter = 0;
    int time_length = string_length(Ctime[0].c_time);
    for(int i = 0; i<time_length; i++){
        if(Ctime[0].c_time[i] == '!'){
            time_counter++;
            break;
        }
        time_counter++;
    }
    //get month
    for(int i = 0; i<5; i++){
        if(Ctime[0].c_time[time_counter] == '#'){
            time_counter++;
            break;
        }
        month[i] = Ctime[0].c_time[time_counter];
        time_counter++;
    }
    // printf("Month : %s\n", month);

    //get day
    for(int i = 0; i<5; i++){
        if(Ctime[0].c_time[time_counter] == '_'){
            time_counter++;
            break;
        }
        day[i] = Ctime[0].c_time[time_counter];
        time_counter++;
    }
    // printf("Day : %s\n", day);

    for(int i = time_counter; i<time_length; i++){
        if(Ctime[0].c_time[i] == '@'){
            time_counter++;
            break;
        }
        time_counter++;
    }

    //get year
    for(int i = 0; i<5; i++){
        if(Ctime[0].c_time[time_counter] == '\0'){
            time_counter++;
            break;
        }
        year[i] = Ctime[0].c_time[time_counter];
        time_counter++;
    }
    // printf("Year : %s\n", year);
    Date date;
    string_copy(date.day, day);
    string_copy(date.month, month);
    string_copy(date.year, year);
    return date;
}

Date get_date_from_record(char note[])
{
    char month[5];
    char day[5];
    char year[5];

    for(int i=0; i<5; i++){
        month[i] = '\0';
        day[i] = '\0';
        year[i] = '\0';
    }

    int note_counter = 0;
    int note_length = string_length(note);
    for(int i = 0; i<note_length; i++){
        if(note[i] == '!'){
            note_counter++;
            break;
        }
        note_counter++;
    }
    //get month
    for(int i = 0; i<5; i++){
        if(note[note_counter] == '#'){
            note_counter++;
            break;
        }
        month[i] = note[note_counter];
        note_counter++;
    }
    // printf("Month : %s\n", month);

    //get day
    for(int i = 0; i<5; i++){
        if(note[note_counter] == '_'){
            note_counter++;
            break;
        }
        day[i] = note[note_counter];
        note_counter++;
    }
    // printf("Day : %s\n", day);

    for(int i = note_counter; i<note_length; i++){
        if(note[i] == '@'){
            note_counter++;
            break;
        }
        note_counter++;
    }

    //get year
    for(int i = 0; i<5; i++){
        if(note[note_counter] == '\0'){
            note_counter++;
            break;
        }
        year[i] = note[note_counter];
        note_counter++;
    }
    // printf("Year : %s\n", year);
    Date date;
    string_copy(date.day, day);
    string_copy(date.month, month);
    string_copy(date.year, year);
    return date;
}

unsigned int get_total_amount_of_same_day(Node* userNode)
{
    unsigned int total_amount = 0;
    Date current_date = get_current_date();
    int record_count = space_array[userNode->data.id - 1001] - 12;
    // printf("Count : %d\n", record_count);
    for(int i=0; i<record_count; i++){
        Date note_date = get_date_from_record(userNode->data.hist[i].note);
        if(string_compare(current_date.year, note_date.year) == 0){
            if(string_compare(current_date.month, note_date.month) == 0){
                if(string_compare(current_date.day, note_date.day) == 0){
                    total_amount += get_amount_from_record(userNode->data.hist[i].note);
                }
            }
        }
    }
    // printf("Total Amount : %u\n", total_amount);
    return total_amount;
}

unsigned int get_amount_from_record(char note[])
{
    char char_amount[10];
    unsigned int amount = 0;
    for(int i = 0; i<10; i++){
        char_amount[i] = '\0';
    }
    int note_length = string_length(note);
    int note_counter = 0;
    for(int i = 0; i<note_length; i++){
        if(note[i] == '$'){
            note_counter++;
            break;
        }
        note_counter++;
    }
    for(int i = 0; i<10; i++){
        if(note[note_counter] == '_'){
            break;
        }
        char_amount[i] = note[note_counter];
        note_counter++;
    }

    //change char array to unsigned int
    FILE *fptr1;
    fptr1 = fopen("atoi.txt", "w");
    if(fptr1 == NULL){
        printf("Error: change char array to integer\n");
        exit(1);
    }else{
        fprintf(fptr1, "%s", char_amount);
    }
    fclose(fptr1);
    FILE *fptr2;
    fptr2 = fopen("atoi.txt", "r");
    if(fptr2 == NULL){
        printf("Error: change char array to integer\n");
        exit(1);
    }else{
        fscanf(fptr2, "%u", &amount);
    }
    fclose(fptr2);
    // printf("Char Amount %s\n", char_amount);
    // printf("Int amount : %u\n", amount);
    return amount;
}