
Calendar Reservation Application-VIT
We all have used a calendar application in our day-to-day lives. This question requires the developer to build an application which achieves the following functionality,

 

1. Register a user

Ability to register a new calendar for a user

 

Input format: 

add-user <user-name>

Output format:

success -> if the request is successful

failure -> if the request fails

 

Example Input:

add-user user1

Corresponding Output:

success

 

This registers a user, “user1” in the system. New events can be created for this user.

Adding the user with the same name multiple times should output “failure” as the response string.

 

2. Create an event with a set of users on a given day + slot

A day is represented in “YYYY-MM-DD” format. Each day consists of 1440 minutes (minute 0 to minute 1439). Duration of an event is configured in “number of minutes”. 

Event slots do not spill over to the next day, slot can be booked only if it is possible to accommodate on the same day itself (max upto 1440th minute)

All event durations would be inclusive of the starting minute and exclusive of the last minute. For example, event during 900-960, would include minute 900 to 959 (inclusive) for the event, 960th minute is available for subsequent event registration. 

 

Input format: 

create-event <day> <start-time> <duration> <number-of-users> <user-list…>   

Output format:

success -> if the request is successful

failure -> if the request fails

 

Example input:

create-event 2021-07-21 600 60 2 user1 user2

create-event 2021-07-21 660 30 2 user1 user2

Corresponding Output:

success

success

 

This creates 2 events with 2 users user1 and user2 on 2021-07-21 at 10am (600th minute) for 1 hour (duration = 60) and at 11am (660th minute) for 30 minutes. 

Output should be “failure” for any wrongly formatted input and in case the event slot is unavailable for any of the requested users. Output should be “success” for correctly formatted input and if the slot is free/bookable for all requested users.

 

3. List events for a user on a given day

Get a list view of all events for a given registered user for a selected day. Each event should be shown as the start and end minute of the event followed by the list of all the users in the event

 

Input format:

show-events <day> <user>

Output format: 

<start-minute>-<end-minute> <user-list...>

 

Sample input:

show-events 2021-07-21 user1

Sample output: 

600-660 user1 user2

…

 

The output is expected to be in a new line for each registered event. So if there are 3 events for a user on the requested day, the output will have 3 lines, each line having event details in the format mentioned above. 

The user names in each event should be in the same order in which they were entered while creating the event. 

The events should be printed in the same sequence in which they were created.

In case there are no events for the selected user for the given day, response string should be “none”

 

4. Suggest first time slot based on availability for a set of users for a given day and time range

Suggest the first available start time for a given list of users for the requested day and time range where all users are available for requested duration. 

 

Input format:

suggest-slot <day> <start-range> <end-range> <duration> <num-of-users> <user-list...>

Output format: 

<first start-time when all users are available for requested duration>

Sample input: 

suggest-slot 2021-07-21 480 720 45 2 user1 user2

Sample output: 

540

 

For feasible input, output should be the first minute in the given time range where all users are available (there should not be any existing event) for the requested duration. 

If not such slot is available, output should be “none”

 

Sample input and output sequence:

Sample input: (first line give count of the input operations for the run of the application)

12 

add-user user1

add-user user2

add-user user3

add-user user4

create-event 2021-07-21 600 60 2 user1 user2

create-event 2021-07-21 660 30 2 user1 user3

create-event 2021-07-21 615 60 2 user2 user3

create-event 2021-07-21 660 30 2 user2 user4

show-events 2021-07-21 user1

show-events 2021-07-21 user2

suggest-slot 2021-07-21 570 750 45 2 user1 user2

suggest-slot 2021-07-21 570 700 60 2 user2 user3

 

Sample output:

success

success

success

success

success

success

failure

success

600-660 user1 user2

660-690 user1 user3

600-660 user1 user2

660-690 user2 user4

690

none

 

Note:

1. Keywords in both the input and output formats need to be exact matches (these keywords are case-sensitive). Response messages should also be exact string matches 

2. Think of logical dependencies between the different types of requests. Input file can have requests in any order. For example, 'add-user' command can be called after other requests as well. Your application should take into account relevant entity dependencies and validations associated with it.

Sample input 1

12 
add-user user1add-user 
user2add-user 
user3add-user 
user4create-event 2021-07-21 600 60 2 user1 user2create-event 2021-07-21 660 30 2 user1 user3create-event 2021-07-21 615 60 2 user2 user3create-event 2021-07-21 660 30 2 user2 user4show-events 2021-07-21 user1
Sample output 1

successsuccesssuccesssuccesssuccesssuccessfailuresuccess600-660 user1 user2660-690 user1 user3
