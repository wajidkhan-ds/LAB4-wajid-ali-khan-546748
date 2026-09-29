#include <iostream>
#include <string>
using namespace std;

// Node for one bit
struct BitNode {
    int bit;          // 0 or 1
    BitNode* prev;
    BitNode* next;
    
    BitNode(int b) {
        bit = b;
        prev = NULL;
        next = NULL;
    }
};

class BinaryNumber {
private:
    BitNode* head;   // Most significant bit
    BitNode* tail;   // Least significant bit

public:
    BinaryNumber() {
        head = NULL;
        tail = NULL;
    }

    // 1. Store binary number from string
    void storeBinary(string bits) {
        // Clear existing
        clear();
        
        // Add each bit as a node
        for (int i = 0; i < bits.length(); i++) {
            int b = bits[i] - '0';
            BitNode* newNode = new BitNode(b);
            
            if (head == NULL) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
        
        cout << "Binary number stored: ";
        display();
    }

    // Clear all nodes
    void clear() {
        BitNode* temp = head;
        while (temp != NULL) {
            BitNode* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = NULL;
    }

    // Display the binary number
    void display() {
        if (head == NULL) {
            cout << "(empty)\n";
            return;
        }
        BitNode* temp = head;
        while (temp != NULL) {
            cout << temp->bit;
            temp = temp->next;
        }
        cout << "\n";
    }

    // Get length
    int length() {
        int count = 0;
        BitNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 2. 1's Complement - flip all bits
    void onesComplement() {
        BitNode* temp = head;
        while (temp != NULL) {
            temp->bit = 1 - temp->bit;  // Flip 0->1, 1->0
            temp = temp->next;
        }
        cout << "1's Complement: ";
        display();
    }

    // 3. 2's Complement - 1's complement + 1
    void twosComplement() {
        // First take 1's complement
        BitNode* temp = head;
        while (temp != NULL) {
            temp->bit = 1 - temp->bit;
            temp = temp->next;
        }
        
        // Now add 1
        addOne();
        
        cout << "2's Complement: ";
        display();
    }

    // Helper: Add 1 to the binary number
    void addOne() {
        BitNode* temp = tail;
        int carry = 1;
        
        while (temp != NULL && carry == 1) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }
        
        // If carry remains, add new node at head
        if (carry == 1) {
            BitNode* newNode = new BitNode(1);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // 4. Binary Addition of two numbers
    BinaryNumber add(BinaryNumber& other) {
        BinaryNumber result;
        
        BitNode* a = tail;              // Start from least significant
        BitNode* b = other.tail;
        int carry = 0;
        string resultStr = "";
        
        while (a != NULL || b != NULL || carry == 1) {
            int sum = carry;
            if (a != NULL) {
                sum += a->bit;
                a = a->prev;
            }
            if (b != NULL) {
                sum += b->bit;
                b = b->prev;
            }
            
            resultStr = char('0' + (sum % 2)) + resultStr;
            carry = sum / 2;
        }
        
        result.storeBinary(resultStr);
        return result;
    }

    // 5. Binary Multiplication (using shifting and addition)
    BinaryNumber multiply(BinaryNumber& other) {
        BinaryNumber result;
        result.storeBinary("0");
        
        string otherStr = other.toString();
        
        // For each bit in other (from right to left)
        for (int i = otherStr.length() - 1; i >= 0; i--) {
            if (otherStr[i] == '1') {
                // Shift this number left by (length - 1 - i) positions
                int shift = otherStr.length() - 1 - i;
                string shifted = toString() + string(shift, '0');
                
                BinaryNumber temp;
                temp.storeBinary(shifted);
                
                result = result.add(temp);
            }
        }
        
        return result;
    }

    // Helper: Convert to string
    string toString() {
        string s = "";
        BitNode* temp = head;
        while (temp != NULL) {
            s += char('0' + temp->bit);
            temp = temp->next;
        }
        return s;
    }

    // 6. Convert to decimal
    int toDecimal() {
        int decimal = 0;
        BitNode* temp = head;
        while (temp != NULL) {
            decimal = decimal * 2 + temp->bit;
            temp = temp->next;
        }
        return decimal;
    }
};

// Main function to test
int main() {
    BinaryNumber b1, b2, result;
    string input;
    int choice;
    
    do {
        cout << "\n===== BINARY ARITHMETIC =====\n";
        cout << "1. Store Binary Number 1\n";
        cout << "2. Store Binary Number 2\n";
        cout << "3. 1's Complement (Num1)\n";
        cout << "4. 2's Complement (Num1)\n";
        cout << "5. Add Num1 + Num2\n";
        cout << "6. Multiply Num1 * Num2\n";
        cout << "7. Convert Num1 to Decimal\n";
        cout << "8. Display Num1\n";
        cout << "9. Display Num2\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter binary number: ";
                cin >> input;
                b1.storeBinary(input);
                break;
            case 2:
                cout << "Enter binary number: ";
                cin >> input;
                b2.storeBinary(input);
                break;
            case 3:
                b1.onesComplement();
                break;
            case 4:
                b1.twosComplement();
                break;
            case 5:
                result = b1.add(b2);
                cout << "Sum: ";
                result.display();
                break;
            case 6:
                result = b1.multiply(b2);
                cout << "Product: ";
                result.display();
                break;
            case 7:
                cout << "Decimal: " << b1.toDecimal() << "\n";
                break;
            case 8:
                cout << "Num1: ";
                b1.display();
                break;
            case 9:
                cout << "Num2: ";
                b2.display();
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