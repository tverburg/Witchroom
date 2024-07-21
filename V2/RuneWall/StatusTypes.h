#define deactivated 0
#define activated 1
#define completed 2
#define openlock 0 //main controller sets this status when lock is supposed to be opened (open on this status)
#define openinglock 1 //main controller sets this status when lock is opening (dont use for opening and closing)
#define openedlock 2 //micro controller sets this status when lock is opened (set status to this when opened)
#define closelock 3 //main controller sets this status when lock is supposed to closed (close on this status)
#define closinglock 4 //main controller sets this status when lock is closing (dont use for opening and closing)
#define closedlock 5 //micro controller set this status hwen lock is closed (set status to this when closed)