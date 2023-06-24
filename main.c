#include "bank.h"

/*
Personal Account
----------------
Wallet Capacity : 1,000,000
Amount Limit Per Day : 500,000

Business Account
----------------
Wallet Capacity : 10,000,000
Amount Limit Per Day : 5,000,000
*/

int main()
{

    space_counter();
    loading_all_data_from_file();
    main_sector();

    return 0;
}