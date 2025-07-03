# Final Project SOW

## Delivarables
I will be making a todo list application. It will be structured sort of like a folder system. You have categories and sub-categories (like folders) which you can put tasks and sub-tasks into.  For example, you might have your categories be UI and Backend for some tech project. Then you would put tasks in here like “Connect to database” under Backend. For each task, you can then open it up and add notes and subtasks. 

I’m modeling this based off a very basic project management system I use in google sheets and google docs, so I’m hoping to simulate that here. In google sheets I have grouped rows under each category, and then the tasks link to a google docs file where you can write notes and put subtasks. The columns in the spreadsheet are Categories, Tasks, Action Date, Due Date, Tag and Rank. This is what I would hope to simulate using c++.

Using tags and dates you can get separate views of your tasks. For example, you might be doing Phase 1 of your project, where you need to complete tasks from both the UI and Backend categories. So you could tag an item under UI, “Make dashboard”, and an item under Backend, “Connect to database”, both with Phase 1. Then you can rank these tasks, and look at a Phase 1 view where you see all your phase 1 tasks listed in order. Date works similarly. There is a “Today” and “This week” feature built in so you can view your tasks for today or the week in a flat list.

## Core Features
1. Order your tasks in a hierarchical project management system
2. Mark completed tasks and have them stored in an archive
3. Add action and due dates to your tasks
4. Tag tasks and then view them through a filtered flat list view
5. Add subtasks and notes to each task

## Special Features
1. It would be nice to integrate this with a calendar. It could automatically put things from your calendar into your “Today” list
2. It would be interesting to remove the hierarchy structure thats built in and have tasks be the fundamental object. The tags you add to tasks could have hierarchy, so then you could have much more control and flexibility over how you view your tasks. From the example above, you could have two main tags, Components and Phases. Each would have subsidiary tags like UI and Backend, and Phase 1 and Phase 2. This is sort of like the difference between a folder system and a data lake. This is something I might even try to implement during this class. I think in this case, tags and tasks would both be classes, and they would be linked to each other

