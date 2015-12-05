typedef enum {
	FieldZoneUnknown = 0x0,
	FieldZoneSkyRise = 0x1,
	FieldZoneNot = 0x2,
	FieldZoneAny = FieldZoneSkyRise | FieldZoneNot
}FieldZone;
typedef enum {
	FieldColorUnknown = 0x0,
	FieldColorRed = 0x1,
	FieldColorBlue = 0x2,
	FieldColorAny = FieldColorRed | FieldColorBlue
}FieldColor;
static bool doneSelection = false;
static FieldZone selectedFieldZone = -1;
static FieldColor selectedFieldColor = -1;
struct AutonomousRoutine {
	AutonomousRoutine *prev;
	AutonomousRoutine *next;
	int zone;
	int color;
	char *name;
	int tag;
}AutonomousRoutine;
static AutonomousRoutine routines[20];
static int slot = 0;
static AutonomousRoutine *first = NULL;
static AutonomousRoutine *selected = NULL;
void AddAutonomousRoutine(FieldZone zone, FieldColor color, char *name, int tag) {
	routines[slot].prev = NULL;
	routines[slot].next = NULL;
	routines[slot].zone = zone;
	routines[slot].color = color;
	routines[slot].name = name;
	routines[slot].tag = tag;
	if (first == NULL){
		first = &routines[slot];
	}
	else{
		AutonomousRoutine *prev = first;
		while(prev->next){
			prev = prev->next;
		}
		routines[slot].prev = prev;
		prev->next = &routines[slot];
	}
	slot++;
}
TControllerButtons waitForButtons(TControllerButtons allowed) {
	TControllerButtons previous = 0;
	TControllerButtons selected = 0;
	while(selected == 0){
		if((allowed & kButtonLeft) != 0 && (previous & kButtonLeft) == kButtonLeft && (nLCDButtons & kButtonLeft) == 0){
			selected = kButtonLeft;
		}
		else if((allowed & kButtonCenter) != 0 && (previous & kButtonCenter) == kButtonCenter && (nLCDButtons & kButtonCenter) == 0){
			selected = kButtonCenter;
		}
		else if ((allowed & kButtonRight) != 0 && (previous & kButtonRight) == kButtonRight && (nLCDButtons & kButtonRight) == 0){
			selected = kButtonRight;
		}
		previous = nLCDButtons;
		wait1Msec(20);
	}
	return selected;
}
task selection() {
	doneSelection = false;
	displayLCDCenteredString(0, "Select Zone");
	displayLCDString(1, 0, "SkyRise");
	displayLCDString(1, 10, "not");
	switch(waitForButtons(kButtonLeft | kButtonRight)){
		case kButtonLeft:
			selectedFieldZone = FieldZoneSkyRise;
			break;
		case kButtonRight:
			selectedFieldZone = FieldZoneNot;
			break;
	}
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, "Select Color");
	displayLCDString(1, 0, "Red");
	displayLCDString(1, 12, "Blue");
	switch (waitForButtons(kButtonLeft | kButtonRight)) {
		case kButtonLeft:
			selectedFieldColor = FieldColorRed;
			break;
		case kButtonRight:
			selectedFieldColor = FieldColorBlue;
			break;
	}
	clearLCDLine(0);
	clearLCDLine(1);
	AutonomousRoutine *routine = first;
	while(routine){
		if((routine->zone & selectedFieldZone) == 0 || (routine->color & selectedFieldColor) == 0){
			if(routine->prev){
				routine->prev->next = routine->next;
			}
			if(routine->next){
				routine->next->prev = routine->prev;
			}
		}
		routine = routine->next;
	}
	displayLCDCenteredString(0, "Select Routine");
	AutonomousRoutine *current = first;
	while(selected == NULL){
		displayLCDCenteredString(1, current->name);
		displayLCDString(1, 0, (current != NULL && current->prev != NULL) ? "<-" : "  ");
		displayLCDString(1, 14, (current != NULL && current->next != NULL) ? "->" : "  ");
		switch(waitForButtons(kButtonLeft | kButtonCenter | kButtonRight)){
			case kButtonLeft:
				if(current != NULL && current->prev != NULL){
					current = current->prev;
				}
				break;
			case kButtonRight:
				if(current != NULL && current->next != NULL){
					current = current->next;
				}
				break;
			case kButtonCenter:
				if(current){
					selected = current;
				}
				break;
		}
	}
	doneSelection = true;
}
void SelectAutonomousRoutine() {
	if(!bIfiRobotDisabled){
		return;
	}
	bLCDBacklight = true;
	StartTask(selection);
	while(!doneSelection){
		if(!bIfiRobotDisabled){
			doneSelection = true;
		}
		wait1Msec(25);
	}
	StopTask(selection);
	bLCDBacklight = false;
}
FieldZone SelectedFieldZone(){
	return selectedFieldZone;
}
FieldColor SelectedFieldColor(){
	return selectedFieldColor;
}
AutonomousRoutine * SelectedAutonomousRoutine(){
	return selected;
}
