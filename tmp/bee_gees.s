.name       "Batman"
.comment    "This city needs me"

loop:
	zjmp%1
	sti r1,%:live, %0
	sti r1,%:loop, %0
	zjmp %1
live:
	live %1
