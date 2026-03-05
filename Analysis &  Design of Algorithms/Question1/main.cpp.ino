#include <Arduino.h>
#define MAX_PLAYLIST_SIZE 10

// TYPE DEFINITIONS
struct Song {
  char title[50];
  char artist[50];
  int duration; // in seconds
};

// Array-based Playlist Implementation
struct ArrayList {
  Song songs[MAX_PLAYLIST_SIZE];
  int size = 0;
};

// Linked List Node Structure
struct SongNode {
  Song song;
  SongNode* next;
};

struct LinkedList {
  SongNode* head = nullptr;
};

// Function prototypes
void addSong(ArrayList* list, const Song& newSong);
void removeSong(ArrayList* list, int index);
void displayPlaylist(const ArrayList* list);
void addSong(LinkedList* list, const Song& newSong);
void removeSong(LinkedList* list, int index);
void displayPlaylist(const LinkedList* list);

// Add song to array list
void addSong(ArrayList* list, const Song& newSong) {
  if (list->size >= MAX_PLAYLIST_SIZE) {
    Serial.println("Error: Playlist is full! Cannot add more songs.");
    return;
  }
  
  list->songs[list->size] = newSong;
  list->size++;
  Serial.println("Song added successfully to array playlist.");
}

// Remove song from array list
void removeSong(ArrayList* list, int index) {
  if (index < 0 || index >= list->size) {
    Serial.println("Error: Invalid index!");
    return;
  }
  
  for (int i = index; i < list->size - 1; i++) {
    list->songs[i] = list->songs[i + 1];
  }
  
  list->size--;
  Serial.println("Song removed successfully from array playlist.");
}

// Display array playlist
void displayPlaylist(const ArrayList* list) {
  if (list->size == 0) {
    Serial.println("Playlist is empty.");
    return;
  }
  
  Serial.println("\n--- Array Playlist ---");
  for (int i = 0; i < list->size; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(list->songs[i].title);
    Serial.print(" by ");
    Serial.print(list->songs[i].artist);
    Serial.print(" [");
    Serial.print(list->songs[i].duration);
    Serial.println(" sec]");
  }
}

// Add song to linked list
void addSong(LinkedList* list, const Song& newSong) {
  SongNode* newNode = new SongNode;
  newNode->song = newSong;
  newNode->next = nullptr;
  
  if (list->head == nullptr) {
    list->head = newNode;
  } else {
    SongNode* current = list->head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
  Serial.println("Song added successfully to linked list playlist.");
}

// Remove song from linked list
void removeSong(LinkedList* list, int index) {
  if (list->head == nullptr) {
    Serial.println("Error: Playlist is empty!");
    return;
  }
  
  if (index < 0) {
    Serial.println("Error: Invalid index!");
    return;
  }
  
  SongNode* toDelete = nullptr;
  
  if (index == 0) {
    toDelete = list->head;
    list->head = list->head->next;
  } else {
    SongNode* current = list->head;
    int currentIndex = 0;
    
    while (current->next != nullptr && currentIndex < index - 1) {
      current = current->next;
      currentIndex++;
    }
    
    if (current->next == nullptr) {
      Serial.println("Error: Index out of bounds!");
      return;
    }
    
    toDelete = current->next;
    current->next = toDelete->next;
  }
  
  delete toDelete;
  Serial.println("Song removed successfully from linked list playlist.");
}

// Display linked list playlist
void displayPlaylist(const LinkedList* list) {
  if (list->head == nullptr) {
    Serial.println("Playlist is empty.");
    return;
  }
  
  Serial.println("\n--- Linked List Playlist ---");
  SongNode* current = list->head;
  int index = 0;
  
  while (current != nullptr) {
    Serial.print(index);
    Serial.print(": ");
    Serial.print(current->song.title);
    Serial.print(" by ");
    Serial.print(current->song.artist);
    Serial.print(" [");
    Serial.print(current->song.duration);
    Serial.println(" sec]");
    
    current = current->next;
    index++;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  // Test Array-based Playlist
  Serial.println("== Testing Array Playlist ==");
  ArrayList myArrayPlaylist;
  addSong(&myArrayPlaylist, {"Song A1", "Artist 1", 180});
  addSong(&myArrayPlaylist, {"Song B2", "Artist 2", 240});
  addSong(&myArrayPlaylist, {"Song C3", "Artist 1", 200});
  displayPlaylist(&myArrayPlaylist);
  removeSong(&myArrayPlaylist, 1);
  Serial.println("After removing index 1:");
  displayPlaylist(&myArrayPlaylist);
  
  // Test Linked List-based Playlist
  Serial.println("\n== Testing Linked List Playlist ==");
  LinkedList myLinkedListPlaylist;
  addSong(&myLinkedListPlaylist, {"Song X1", "Artist X", 195});
  addSong(&myLinkedListPlaylist, {"Song Y2", "Artist Y", 225});
  addSong(&myLinkedListPlaylist, {"Song Z3", "Artist Z", 215});
  displayPlaylist(&myLinkedListPlaylist);
  removeSong(&myLinkedListPlaylist, 1);
  Serial.println("After removing index 1:");
  displayPlaylist(&myLinkedListPlaylist);
  
  // Clean up linked list
  SongNode* current = myLinkedListPlaylist.head;
  while (current != nullptr) {
    SongNode* temp = current;
    current = current->next;
    delete temp;
  }
  
  /*
  ANALYSIS:
  
  1. For a playlist that rarely changes, array implementation is more memory-efficient
     because it has no overhead per element (no pointers needed).
  
  2. For frequent additions/removals from the middle, linked list is more time-efficient
     because no shifting of elements is required.
  
  3. Risk of linked list on ESP32: Memory fragmentation over time due to frequent
     new/delete operations can cause allocation failures.
  */
}

void loop() {
  // Nothing to do here
}

