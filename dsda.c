#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10000

typedef struct Tweet {
    int tweetId;
    char message[100];
    struct Tweet* next;
} Tweet;

typedef struct User {
    int userId;
    char userName[50];
    int following[MAX_USERS];
    Tweet* tweets;
} User;

typedef struct Twitter {
    User users[MAX_USERS];
} Twitter;

typedef struct UserNode {
    User* user;
    struct UserNode* left;
    struct UserNode* right;
} UserNode;

UserNode* createUserNode(User* user) {
    UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
    newNode->user = user;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

UserNode* insertUserNode(UserNode* root, User* user) {
    if (root == NULL) {
        return createUserNode(user);
    }
    if (strcmp(user->userName, root->user->userName) < 0) {
        root->left = insertUserNode(root->left, user);
    } else {
        root->right = insertUserNode(root->right, user);
    }
    return root;
}

User* searchUser(UserNode* root, const char* userName) {
    if (root == NULL || strcmp(root->user->userName, userName) == 0) {
        return root ? root->user : NULL;
    }
    if (strcmp(userName, root->user->userName) < 0) {
        return searchUser(root->left, userName);
    } else {
        return searchUser(root->right, userName);
    }
}

Twitter* twitterCreate() {
    Twitter* obj = (Twitter*)malloc(sizeof(Twitter));
    for (int i = 0; i < MAX_USERS; i++) {
        obj->users[i].userId = i;
        obj->users[i].tweets = NULL;
        memset(obj->users[i].following, 0, sizeof(obj->users[i].following));
        obj->users[i].userName[0] = '\0';
    }
    return obj;
}

void twitterPostTweet(Twitter* obj, User* user, int tweetId, const char* message) {
    Tweet* newTweet = (Tweet*)malloc(sizeof(Tweet));
    newTweet->tweetId = tweetId;
    strncpy(newTweet->message, message, sizeof(newTweet->message) - 1);
    newTweet->message[sizeof(newTweet->message) - 1] = '\0';
    newTweet->next = user->tweets;
    user->tweets = newTweet;
}

void displayUserTweets(User* user) {
    printf("Tweets by %s:\n", user->userName);
    Tweet* t = user->tweets;
    while (t) {
        printf("Tweet ID: %d, Message: %s\n", t->tweetId, t->message);
        t = t->next;
    }
}

void followUser(Twitter* obj, int followerId, int followeeId) {
    if (followerId < 0 || followeeId < 0 || followerId >= MAX_USERS || followeeId >= MAX_USERS) {
        return;
    }
    obj->users[followerId].following[followeeId] = 1;
}

void unfollowUser(Twitter* obj, int followerId, int followeeId) {
    if (followerId < 0 || followeeId < 0 || followerId >= MAX_USERS || followeeId >= MAX_USERS) {
        return;
    }
    obj->users[followerId].following[followeeId] = 0;
}

void getNewsFeed(Twitter* obj, int userId) {
    if (userId < 0 || userId >= MAX_USERS) {
        return;
    }
    printf("Feed for User %d:\n", userId);

    Tweet* stack[100]; 
    int top = -1; 

    for (int i = 0; i < MAX_USERS; i++) {
        if (i == userId || obj->users[userId].following[i]) {
            Tweet* t = obj->users[i].tweets;
            while (t) {
                stack[++top] = t;
                t = t->next;
            }
        }
    }

    int count = 0;
    while (top >= 0 && count < 10) {
        Tweet* t = stack[top--];
        printf("Tweet ID: %d, Message: %s\n", t->tweetId, t->message);
        count++;
    }
}

void freeUserTree(UserNode* root) {
    if (root == NULL) {
        return;
    }
    freeUserTree(root->left);
    freeUserTree(root->right);
    free(root);
}

int main() {
    int choice;
    Twitter* obj = twitterCreate();
    UserNode* userTree = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Post a tweet\n");
        printf("2. Follow a user\n");
        printf("3. Get feed\n");
        printf("4. Unfollow a user\n");
        printf("5. Search user by name\n");
        printf("6. Exit the platform\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int userId, tweetId;
            char userName[50], message[100];
            printf("\nEnter user ID and username: ");
            scanf("%d %s", &userId, userName);
            if (obj->users[userId].userName[0] == '\0') {
                strcpy(obj->users[userId].userName, userName);
                userTree = insertUserNode(userTree, &obj->users[userId]);
            }
            printf("Enter tweet ID and message: ");
            scanf("%d %s", &tweetId, message);
            twitterPostTweet(obj, &obj->users[userId], tweetId, message);
            printf("Tweet posted successfully!\n");
            break;
        }
        case 2: {
            int followerId, followeeId;
            printf("\nEnter follower ID and followee ID: ");
            scanf("%d %d", &followerId, &followeeId);
            followUser(obj, followerId, followeeId);
            break;
        }
        case 3: {
            int userId;
            printf("\nEnter user ID to get feed: ");
            scanf("%d", &userId);
            getNewsFeed(obj, userId);
            break;
        }
        case 4: {
            int followerId, followeeId;
            printf("\nEnter follower ID and followee ID: ");
            scanf("%d %d", &followerId, &followeeId);
            unfollowUser(obj, followerId, followeeId);
            break;
        }
        case 5: {
            char userName[50];
            printf("\nEnter the username to search: ");
            scanf("%s", userName);
            User* user = searchUser(userTree, userName);
            if (user) {
                printf("User found: %s ID: %d\n", user->userName, user->userId);
                displayUserTweets(user);
            } else {
                printf("User not found.\n");
            }
            break;
        }
        case 6: {
            freeUserTree(userTree);
            free(obj);
            return 0;
        }
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
