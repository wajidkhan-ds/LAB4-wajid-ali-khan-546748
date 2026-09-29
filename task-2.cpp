#include <iostream>
using namespace std;

// Node for a person
struct Person {
    int id;
    Person* next;
    
    Person(int i) {
        id = i;
        next = NULL;
    }
};

class JosephusCircle {
private:
    Person* head;
    int totalPeople;

public:
    JosephusCircle() {
        head = NULL;
        totalPeople = 0;
    }

    // 1. Create circular list of N people
    void createCircle(int n) {
        totalPeople = n;
        head = NULL;
        
        if (n <= 0) return;
        
        // Create first person
        head = new Person(1);
        Person* temp = head;
        
        // Create rest and link circularly
        for (int i = 2; i <= n; i++) {
            Person* newPerson = new Person(i);
            temp->next = newPerson;
            temp = newPerson;
        }
        
        // Make it circular
        temp->next = head;
        
        cout << "Circle created with " << n << " people.\n";
    }

    // Display current circle
    void displayCircle() {
        if (head == NULL) {
            cout << "Circle is empty.\n";
            return;
        }
        
        cout << "Circle: ";
        Person* temp = head;
        do {
            cout << temp->id << " ";
            temp = temp->next;
        } while (temp != head);
        cout << "\n";
    }

    // 2 & 3. Elimination process and display eliminated order
    void eliminate(int k) {
        if (head == NULL) {
            cout << "Circle is empty.\n";
            return;
        }
        
        cout << "\n--- Elimination Order ---\n";
        
        Person* current = head;
        Person* prev = NULL;
        
        // Find the last person (to help with deletion)
        Person* last = head;
        while (last->next != head) {
            last = last->next;
        }
        
        int remaining = totalPeople;
        
        while (remaining > 1) {
            // Count k-1 steps forward (current is at 1)
            for (int i = 1; i < k; i++) {
                prev = current;
                current = current->next;
            }
            
            // Eliminate current person
            cout << "Eliminated: " << current->id << "\n";
            
            // Remove current from circle
            if (current == head) {
                // If head is eliminated
                last->next = current->next;
                head = current->next;
            } else {
                prev->next = current->next;
            }
            
            Person* toDelete = current;
            current = current->next;
            delete toDelete;
            
            remaining--;
        }
        
        // 4. Display survivor
        cout << "\n*** Survivor: Person " << head->id << " ***\n";
    }
};

// Main function
int main() {
    JosephusCircle jc;
    int n, k;
    
    cout << "===== JOSEPHUS PROBLEM =====\n";
    cout << "Enter number of people (N): ";
    cin >> n;
    cout << "Enter step count (k): ";
    cin >> k;
    
    jc.createCircle(n);
    jc.displayCircle();
    jc.eliminate(k);
    
    return 0;
}