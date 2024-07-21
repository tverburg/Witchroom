class StatusTypes:
    deactivated = 0
    activated = 1
    completed = 2
    openlock = 0 #main controller sets this status when lock is supposed to be opened (open on this status)
    openinglock = 1 #main controller sets this status when lock is opening (dont use for opening and closing)
    openedlock = 2 #micro controller sets this status when lock is opened (set status to this when opened)
    closelock = 3 #main controller sets this status when lock is supposed to closed (close on this status)
    closinglock = 4 #main controller sets this status when lock is closing (dont use for opening and closing)
    closedlock = 5 #micro controller set this status hwen lock is closed (set status to this when closed)