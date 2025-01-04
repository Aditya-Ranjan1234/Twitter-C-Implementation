# Twitter-C-Implementation

This project is part of the **Data Structures and Algorithms (DSDA) Lab** for college. It implements a simplified version of a Twitter-like platform using C. The application supports user registration, posting tweets, following/unfollowing users, viewing news feeds, and searching users by name.

---

## Features

1. **Post Tweets**  
   Users can post tweets with a unique tweet ID and a short message.

2. **Follow/Unfollow Users**  
   Users can follow or unfollow other users to manage their news feeds.

3. **View News Feed**  
   Retrieve the latest tweets from followed users and display up to 10 recent tweets.

4. **Search Users by Username**  
   Search for users by their username using a binary search tree for efficient lookup.

5. **Display Tweets**  
   View all tweets posted by a specific user.

---

## How to Run the Project

1. Clone the repository or download the code.  
   ```bash
   git clone https://github.com/Aditya-Ranjan1234/Twitter-C-Implementation.git
   ```
2. Compile the C program using a compiler like GCC:  
   ```bash
   gcc -o twitter_simulation dsda-el.c
   ```
3. Run the executable:  
   ```bash
   ./twitter_simulation
   ```

---

## Menu Options

When running the program, you can select from the following options:

1. **Post a Tweet**: Enter the user ID, username, tweet ID, and the message.  
2. **Follow a User**: Enter the follower ID and followee ID.  
3. **Get News Feed**: View recent tweets for a specific user ID.  
4. **Unfollow a User**: Remove a follow relationship.  
5. **Search User by Name**: Search for a user by their username and view their details.  
6. **Exit**: Exit the platform and free all allocated memory.

---

## Data Structures Used

- **Binary Search Tree (BST)**:  
  Used for efficient user lookup by username.

- **Stack**:  
  Utilized to store and manage tweets for quick access.

- **Linked List**:  
  Stores tweets for each user.

---

## Code Highlights

1. **Binary Search Tree for User Search**:  
   Efficiently searches users by their username for faster results.

2. **Stack for News Feed**:  
   Provides a way to retrieve the latest tweets efficiently.

3. **Dynamic Memory Management**:  
   Ensures proper allocation and deallocation of memory for user and tweet data.

---

## Authors

- **Aditya Ranjan**
- **Gnanendra Naidu**
- **Ahibhruth A**
- **Garv Agarwalla** 

---

## License

This project is licensed under the GNU License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- DSDA Lab Faculty for their guidance.
- Fellow classmates for brainstorming ideas.

