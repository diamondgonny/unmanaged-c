#include <assert.h>
#include <time.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;

    assert(TRUE == add_item("Magarita", 12.45));
    assert(TRUE == add_item("Sharkfin soup", 500.12));
    assert(TRUE == add_item("Kingcrab dip", 125.99));
    assert(TRUE == add_item("Deep fried scallops", 7.36));
    assert(TRUE == add_item("Tacoyaki", 6.89));
    assert(TRUE == add_item("Salmon sashimi", 16.54));
    assert(TRUE == add_item("Tuna sashimi", 15.42));
    assert(TRUE == add_item("Unagi soup", 25.48));
    assert(TRUE == add_item("Nestea ice tea", 5.99));
    assert(TRUE == add_item("Chocolate brownie fudge", 8.99));

    assert(FALSE == add_item("This won't get added lol", 2.55));

    set_tip(20.55);

    set_message("Thanks for dining with us!");

    assert(TRUE == print_receipt("receipt0.txt", time));

    assert(TRUE == add_item("Raw sea cucumber", 34.26));
    assert(TRUE == add_item("Pan fried Mackerel", 16.58));
    assert(TRUE == add_item("Pepsi", 5.99));

    assert(TRUE == print_receipt("receipt1.txt", time));

    set_message("My message");

    assert(FALSE == print_receipt("receipt2.txt", time));

    assert(TRUE == add_item("Strawberry Shortcake", 15));

    set_tip(5);

    assert(TRUE == print_receipt("receipt3.txt", time));

	return 0;
}

/* receipt.txt */
/*
Charles'.Seafood⤶
--------------------------------------------------⤶
2019-08-24.22:44:41..........................00512⤶
--------------------------------------------------⤶
.........................Scallops............24.55⤶
.............................Crab............21.45⤶
..........................Sashimi............15.50⤶
⤶
.........................Subtotal............61.50⤶
..............................Tax.............3.08⤶
............................Total............64.58⤶
⤶
Thank you for dining with us today! We will wait f⤶
or your next visit!⤶
==================================================⤶
........................................Tax#-51234
*/
