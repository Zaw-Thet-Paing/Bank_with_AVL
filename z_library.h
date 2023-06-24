struct NRC_DB{
    char nrc[25];
};

struct NRC_DB nrcDB[45];

int string_compare(char str1[], char str2[]);
int string_length(char str[]);
void string_copy(char dest[], char src[]);

int check_input(char input[10]);
int is_strong_password(char password[]);
int is_valid_email(char email[]);
int is_NRC_valid(char nrc[]);
int is_phone_valid(char phone[]);
int is_accountType_valid(char account_type[]);
int is_space(char text[]);

void int_to_char_array(int num, char* arr);

void load_data_to_nrc_db();

int check_input(char input[10])
{
    if(input[0] >= 48 && input[0] <= 57 && input[1] == '\0'){
        return input[0];
    }
    return -1;
}

void string_copy(char dest[], char src[])
{   
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int string_compare(char str1[], char str2[])
{
    int i = 0;
    while (str1[i] && (str1[i] == str2[i])) {
        i++;
    }

    return (str1[i] - str2[i]);
}

int string_length(char str[])
{
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int is_strong_password(char password[])
{
    int upperCase = 0;
    int lowerCase = 0;
    int digit = 0;
    int specialChar = 0;
    int length  = 0;

    while(password[length] != '\0'){
        if(password[length] >= 'a' && password[length] <= 'z'){
            lowerCase = 1;
        }else if(password[length] >= 'A' && password[length] <= 'Z'){
            upperCase = 1;
        }else if(password[length] >= '0' && password[length] <= '9'){
            digit = 1;
        }else if(password[length] >= '!' && password[length] <= '/'){
            specialChar = 1;
        }else if(password[length] >= ':' && password[length] <= '@'){
            specialChar = 1;
        }else if(password[length] >= '[' && password[length] <= '`'){
            specialChar = 1;
        }else if(password[length] >= '{' && password[length] <= '~'){
            specialChar = 1;
        }
        length++;
    }
    return ( upperCase && lowerCase && digit && specialChar && length >= 8 );
}

int is_valid_email(char email[])
{
    int space = 0;
    int at_count = 0;
    int email_length = string_length(email);
    char domain_to_check[20] = "gmail.com";
    char email_domain[20];
    //add '\0'
    for(int i = 0; i<20; i++){
        email_domain[i] = '\0';
    }
    //space exists checking
    for(int i = 0; i<email_length; i++){
        if(email[i] == ' '){
            space = 1;
            break;
        }
    }
    if(space == 0){
        // @ count
        for(int i = 0; i<email_length; i++){
            if(email[i] == '@'){
                at_count++;
            }
        }

        if(at_count == 1){
            //find index of @
            int at_index = 0;
            for(int i = 0; i<email_length; i++){
                if(email[i] == '@'){
                    at_index = i;
                    break;
                }
            }
            //put domain to variable
            int j = 0;
            for(int i = at_index+1; i<email_length; i++){
                email_domain[j] = email[i];
                j++;
            }

            //check domain is gmail.com or not
            if(string_compare(domain_to_check, email_domain) == 0){
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    
}

//only available for Yangon
int is_NRC_valid(char nrc[])
{
    load_data_to_nrc_db();
    int nrc_length = string_length(nrc);
    int nrc_format_end_index = 0;
    char nrc_format[15];
    char nrc_number[15];
    //put \0 to empty array
    for(int i = 0; i<15; i++){
        nrc_format[i] = '\0';
        nrc_number[i] = '\0';
    }

    //find format end index
    for(int i = 0; i<nrc_length; i++){
        if(nrc[i] == ')'){
            nrc_format_end_index = i;
            break;
        }
    }

    if(nrc_format_end_index != 0){
        //put data to nrc_format
        for(int i = 0; i<(nrc_format_end_index+1); i++){
            nrc_format[i] = nrc[i];
        }

        int flag = 0;
        for(int i = 0; i<45; i++){
            if(string_compare(nrcDB[i].nrc, nrc_format) == 0){
                flag = 1;
                break;
            }
        }

        if(flag != 0){
            //put data to nrc_number
            int j = 0;
            for(int i = (nrc_format_end_index+1); i<nrc_length; i++){
                nrc_number[j] = nrc[i];
                j++;
            }
            
            if(string_length(nrc_number) == 6){
                return 1;
            }else{
                return 0;
            }

        }else{
            return 0;
        }

    }else{
        return 0;
    }
}

int is_phone_valid(char phone[])
{
    int space_count = 0;
    int phone_length = string_length(phone);
    for(int i = 0; i<phone_length; i++){
        if(phone[i] == ' '){
            space_count++;
            break;
        }
    }

    if(space_count == 0){
        if(phone_length == 12){
            if(phone[0] == '9' && phone[1] == '5' && phone[2] == '9'){
                return 1;
            }else{
                return 0;
            }
        }else{  
            return 0;
        }
    }else{
        return 0;
    }
}

int is_accountType_valid(char account_type[])
{
    if(string_compare(account_type, "Personal") == 0 || string_compare(account_type, "Business") == 0){
        return 1;
    }
    return 0;
}

int is_space(char text[])
{
    if(text[0] != '\0'){
        int text_count = string_length(text);
        for(int i = 0; i<text_count; i++){
            if(text[i] == ' '){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void load_data_to_nrc_db()
{
    string_copy(nrcDB[0].nrc, "12/AaLaNa(N)");
    string_copy(nrcDB[1].nrc, "12/BaHaNa(N)");
    string_copy(nrcDB[2].nrc, "12/BaTaHta(N)");
    string_copy(nrcDB[3].nrc, "12/KaKaKa(N)");
    string_copy(nrcDB[4].nrc, "12/DaGaNa(N)");
    string_copy(nrcDB[5].nrc, "12/DaGaYa(N)");
    string_copy(nrcDB[6].nrc, "12/DaGaMa(N)");
    string_copy(nrcDB[7].nrc, "12/DaSaKa(N)");
    string_copy(nrcDB[8].nrc, "12/DaGaTa(N)");
    string_copy(nrcDB[9].nrc, "12/DaLaNa(N)");
    string_copy(nrcDB[10].nrc, "12/DaPaNa(N)");
    string_copy(nrcDB[11].nrc, "12/LaMaNa(N)");
    string_copy(nrcDB[12].nrc, "12/LaThaYa(N)");
    string_copy(nrcDB[13].nrc, "12/LaKaNa(N)");
    string_copy(nrcDB[14].nrc, "12/MaBaNa(N)");
    string_copy(nrcDB[15].nrc, "12/HtaTaPa(N)");
    string_copy(nrcDB[16].nrc, "12/AhSaNa(N)");
    string_copy(nrcDB[17].nrc, "12/KaMaYa(N)");
    string_copy(nrcDB[18].nrc, "12/KhaYaNa(N)");
    string_copy(nrcDB[19].nrc, "12/KaKhaKa(N)");
    string_copy(nrcDB[20].nrc, "12/KaTaTa(N)");
    string_copy(nrcDB[21].nrc, "12/KaTaNa(N)");
    string_copy(nrcDB[22].nrc, "12/KaMaTa(N)");
    string_copy(nrcDB[23].nrc, "12/LaMaTa(N)");
    string_copy(nrcDB[24].nrc, "12/LaThaNa(N)");
    string_copy(nrcDB[25].nrc, "12/MaYaKa(N)");
    string_copy(nrcDB[26].nrc, "12/MaGaTa(N)");
    string_copy(nrcDB[27].nrc, "12/MaGaDa(N)");
    string_copy(nrcDB[28].nrc, "12/OuKaMa(N)");
    string_copy(nrcDB[29].nrc, "12/PaBaTa(N)");
    string_copy(nrcDB[30].nrc, "12/PaZaDa(N)");
    string_copy(nrcDB[31].nrc, "12/SaKhaNa(N)");
    string_copy(nrcDB[32].nrc, "12/SaKaKha(N)");
    string_copy(nrcDB[33].nrc, "12/SaKaNa(N)");
    string_copy(nrcDB[34].nrc, "12/YaPaKa(N)");
    string_copy(nrcDB[35].nrc, "12/YaPaTha(N)");
    string_copy(nrcDB[36].nrc, "12/OuKaTa(N)");
    string_copy(nrcDB[37].nrc, "12/TaKaNa(N)");
    string_copy(nrcDB[38].nrc, "12/TaMaNa(N)");
    string_copy(nrcDB[39].nrc, "12/ThaKaTa(N)");
    string_copy(nrcDB[40].nrc, "12/ThaLaNa(N)");
    string_copy(nrcDB[41].nrc, "12/ThaGaKa(N)");
    string_copy(nrcDB[42].nrc, "12/ThaKhaNa(N)");
    string_copy(nrcDB[43].nrc, "12/TaTaNa(N)");
    string_copy(nrcDB[44].nrc, "12/YaKaNa(N)");
}

void int_to_char_array(int num, char* arr)
{
    sprintf(arr, "%d", num);
}