# plant_scheduler


### This was completed as part of a coding challenge. The coding challenge was open for a week, but I found out about it about 4 days before hand. The challenge was to create a application that would present the user with the plants that need to be watered on that day. The plants and their watering intervals were provided in a JSON file that needed to be parsed in order to produce the calander for the user. Plants are never watered on the weekends! It is acceptable to vary by as much as a day for each plants watering requirements, for instance in order to take a break during the weekends. 


pull repository, then make to compile. 

## Usage:
./plant_scheduler [-o n]
	-o for offset- go forward X number of days in the schedule to see what needs watering then.

## Features:
	* Will warn if json file not found
	* Will display usage statement if incorrect parameters used

## Future additions:
	* I would like to add the capacity to add new entries to the JSON file through the ./plant_scheduler program.
	* I would like to be able to take the date from user, rather than using an offset.
	* I need to make it easier to actually optimize the watering schedule based on the input files. Watering day assignment isn't very optimized, although the code is generally extensible in terms that it would be easy to add more plants. Testing with different watering intervals will be problematic as it stands.	
