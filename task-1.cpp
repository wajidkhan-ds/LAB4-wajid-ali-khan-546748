#include <iostream>
#include <string>
using namespace std;

// Node structure for a song
struct Song {
    int id;
    string name;
    Song* prev;
    Song* next;
    
    Song(int i, string n) {
        id = i;
        name = n;
        prev = NULL;
        next = NULL;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;  // For "play next/previous" simulation

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        current = NULL;
    }

    // 1. Add song at end
    void addSong(int id, string name) {
        Song* newSong = new Song(id, name);
        
        if (head == NULL) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song added: " << name << " (ID: " << id << ")\n";
    }

    // 2. Delete song by ID
    void deleteSong(int id) {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }
        
        Song* temp = head;
        
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        
        if (temp == NULL) {
            cout << "Song with ID " << id << " not found.\n";
            return;
        }
        
        // If deleting head
        if (temp == head) {
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
        }
        // If deleting tail
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        }
        // If deleting middle node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        
        // Update current if it was pointing to deleted song
        if (current == temp) {
            current = head;
        }
        
        cout << "Song deleted: " << temp->name << "\n";
        delete temp;
    }

    // 3. Display forward
    void displayForward() {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }
        
        cout << "\n--- Playlist (Forward) ---\n";
        Song* temp = head;
        while (temp != NULL) {
            cout << "ID: " << temp->id << " | Song: " << temp->name << "\n";
            temp = temp->next;
        }
        cout << "--------------------------\n";
    }

    // 4. Display backward
    void displayBackward() {
        if (tail == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }
        
        cout << "\n--- Playlist (Backward) ---\n";
        Song* temp = tail;
        while (temp != NULL) {
            cout << "ID: " << temp->id << " | Song: " << temp->name << "\n";
            temp = temp->prev;
        }
        cout << "---------------------------\n";
    }

    // 5. Search song by ID
    void searchSong(int id) {
        Song* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Found -> ID: " << temp->id 
                     << " | Song: " << temp->name << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song with ID " << id << " not found.\n";
    }

    // 6. Play next song
    void playNext() {
        if (current == NULL) {
            cout << "No song is currently playing.\n";
            return;
        }
        if (current->next == NULL) {
            cout << "This is the last song. No next song.\n";
            return;
        }
        current = current->next;
        cout << "Now playing: " << current->name 
             << " (ID: " << current->id << ")\n";
    }

    // 6. Play previous song
    void playPrevious() {
        if (current == NULL) {
            cout << "No song is currently playing.\n";
            return;
        }
        if (current->prev == NULL) {
            cout << "This is the first song. No previous song.\n";
            return;
        }
        current = current->prev;
        cout << "Now playing: " << current->name 
             << " (ID: " << current->id << ")\n";
    }

    // 7. Reverse playlist in place
    void reversePlaylist() {
        if (head == NULL || head == tail) {
            cout << "Nothing to reverse.\n";
            return;
        }
        
        Song* temp = NULL;
        Song* curr = head;
        
        // Swap next and prev for all nodes
        while (curr != NULL) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;  // Move to next node (which is now prev)
        }
        
        // Swap head and tail
        temp = head;
        head = tail;
        tail = temp;
        
        cout << "Playlist reversed successfully.\n";
    }
};

// Main function to test
int main() {
    Playlist p;
    int choice, id;
    string name;
    
    do {
        cout << "\n===== PLAYLIST MENU =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Forward\n";
        cout << "4. Display Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next\n";
        cout << "7. Play Previous\n";
        cout << "8. Reverse Playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter Song ID: ";
                cin >> id;
                cout << "Enter Song Name: ";
                cin >> name;
                p.addSong(id, name);
                break;
            case 2:
                cout << "Enter Song ID to delete: ";
                cin >> id;
                p.deleteSong(id);
                break;
            case 3:
                p.displayForward();
                break;
            case 4:
                p.displayBackward();
                break;
            case 5:
                cout << "Enter Song ID to search: ";
                cin >> id;
                p.searchSong(id);
                break;
            case 6:
                p.playNext();
                break;
            case 7:
                p.playPrevious();
                break;
            case 8:
                p.reversePlaylist();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    
    return 0;
}