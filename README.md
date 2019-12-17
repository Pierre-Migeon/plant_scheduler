# plant_scheduler


This was completed as part of a coding challenge. The coding challenge was open for a week, but I found out about it about 4 days before hand. The challenge was to create a application that would present the user with the plants that need to be watered on that day. The plants and their watering intervals were provided in a JSON file that needed to be parsed in order to produce the calander for the user. Plants are never watered on the weekends! 


pull repository, then make to compile. 

Usage:
	./plant_scheduler [-o n]
		-o for offset- go forward X number of days in the schedule to see what needs watering then.


Features:
	Will warn if json file not found 

Future additions:
	I would like to add the capacity to add new entries to the JSON file through the ./plant_scheduler program. 
