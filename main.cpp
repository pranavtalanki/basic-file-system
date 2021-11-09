#include <bits/stdc++.h>
#include <vector>
#include <string>
#define name_max 100
using namespace std;

// File structure
struct Node
{
    //Mentioning all attributes that are needed in a file system.
    bool status;
    int file_number;
    string name;
    float size;
    string type;          // folder or if its like pdf or ppt
    vector<Node *> child; // dynamic array
};

// Function to create new node
Node *newNode(int key, string f_name, float size_, string type)
{
    Node *temp = new Node;
    temp->file_number = key;
    //cout<<"For node "<<key<<":";
    //cout<<"\nEnter file name: ";
    temp->name = f_name;
    //cout<<"\nEnter file size: ";
    temp->size = size_;
    temp->type = type;
    temp->status = true;
    return temp;
}

// To view all files we use traversal function
void Traversal(Node *root)
{
    int i,n;
    cout << "\n--------------------------------------------------\n";
    cout << "\n\t\t\t***FILE SYSTEM***\n";
    if (root == NULL)
        return;

    // we can traverse using queues.
    queue<Node *> q; // Create a queue
    q.push(root);    // Enqueue root
    while (!q.empty())
    {
        n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node *p = q.front();
            q.pop();
            if (p->status)
            {
                cout << "\nfile number: " << p->file_number;
                cout << "\nfile name: " << p->name;
                cout << "\nfile size: " << p->size;
                cout << "\nFile type: " << p->type;
            }
            cout << "\nThe children include: (";
            // Enqueue all children of the dequeued item
            for (i = 0; i < p->child.size(); i++)
            {
                if (p->child[i]->status)
                {
                    cout << p->child[i]->file_number << ", ";
                    q.push(p->child[i]);
                }
            }
            cout << ")\n";
            n--;
            if (n == 0)
            {
                cout << "\nThe children for above nodes are:\n";
            }
        }
        cout << "\n"; // Print new line between two levels
    }
    cout << "\n--------------------------------------------------\n";
}



//another function that runs inside delete function. //dynamically changes size of the folder.
void Modify_file_size(int f_number, Node *root, float input_size,int option)
{
    int i,n;
    if (root == NULL)
        return;

    queue<Node *> q; // Create a queue
    q.push(root);    // Enqueue root
    while (!q.empty())
    {
        n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node *p = q.front();
            q.pop();
            for (i = 0; i < p->child.size(); i++)
            {
                if (p->child[i]->file_number == f_number)
                {
                    if(option == 1) //Insertion function called size function so increment is needed.
                    {
                        if(p->file_number == root->file_number)
                        {
                            return;
                        }
                        else
                        {
                            p->size += input_size;
                            Modify_file_size(p->file_number,root,input_size,1);
                        }
                    }
                    else if(option == 2) // deletion function called size function so decrement is needed.
                    {
                        if(p->file_number == root->file_number)
                        {
                            return;
                        }
                        else
                        {
                            p->size -= input_size;
                            Modify_file_size(p->file_number,root,input_size,2);
                        }
                    }
                }
            }
            for (i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
    }
}

void Insert_Node(Node *root)
{
    cout << "\n--------------------------------------------------\n";
    cout << "\n\t\t\t***INSERTION***\n";
    cout << "\nEnter where you want to add file/folder (enter Folder number): ";
    int number,i,n;
    int key;
    string f_name;
    float size_;
    string type;
    cin >> number;
    /*int flag = 0;
    for(auto& it : temp->child)
    {
        if(it->file_number == number)
        {
            cout<<"\nFile in this region found";

        }
    } */
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        while (n > 0)
        {
            Node *p = q.front();
            q.pop();
            if (p->file_number == number)
            {
                if (p->type == "Folder")
                {
                    cout << "\nThe given folder exists\n";
                    cout << "\nEnter file number(mostly in chronological order): ";
                    cin >> key;
                    cout << "\nEnter file name(string): ";
                    // in order to ignore the leading whitespace characters when giving multiple inputs
                    // we use cin.ignore()
                    cin.ignore();
                    getline(cin, f_name);
                    cout << "\nEnter file type(if application mention type or if folder than mention Folder): ";
                    cin >> type;
                    if(type == "Folder")
                    {
                        size_ = 0.0;
                        p->size = size_;
                    }
                    else
                    {
                        cout << "\nEnter file size(taken in as Mb, can be float values as well): ";
                        cin >> size_;
                        //p->size += size_;
                        //root->size += p->size;
                    }
                    // new node function should be below.
                    (p->child).push_back(newNode(key, f_name, size_, type));
                    Modify_file_size(key,root,size_,1);
                    root->size += size_;
                    cout << "\nNew node Inserted\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
                else
                {
                    cout << "\n\t\t\t***ERROR***";
                    cout << "\nThe given file type is not a folder so it will not take another file as its child\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
            }
            for (i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
    }
}

//deletion function
void Delete_Node(Node *root, int number)
{
    int i,n;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        while (n > 0)
        {
            Node *p = q.front();
            q.pop();
            if (p->file_number == number)
            {
                if (p->file_number == 1 || p->file_number == 2 || p->file_number == 3 || p->file_number == 4)
                {
                    cout << "\n\t\t\t\t***ERROR***\nDeleting main directories not possible\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
                else
                {
                    if (p->status)
                    {
                        p->status = false;
                        Modify_file_size(number, root, p->size,2);
                        root->size -= p->size;
                        //delete(p);
                        for (int i = 0; i < p->child.size(); i++)
                        {
                            p->child[i]->status = false;
                            p->child[i]->size = 0;
                        }
                        cout << "\nDELETED\n";
                        cout << "\n--------------------------------------------------\n";
                        return;
                    }
                }
            }
            for (i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
    }
}

//Modifying function
void Modify_node_position(Node *root)
{
    cout << "\n--------------------------------------------------\n";
    cout << "\n\t\t\t***Details Modifying***\n";
    int number,i,n;
    //bool status1;
    string name1;
    float size1;
    string type1;
    cout << "\nEnter what file / folder to modify the position\n ";
    cin >> number;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        while (n > 0)
        {
            Node *p = q.front();
            q.pop();
            if (p->file_number == number)
            {
                name1 = p->name;
                size1 = p->size;
                type1 = p->type;
            }
            for (i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
    }
    Delete_Node(root, number);
    cout << "\nEnter where you want to move file/folder (enter Folder number): ";
    int number1;
    cin >> number1;
    queue<Node *> q1;
    q1.push(root);
    while (!q1.empty())
    {
        n = q1.size();
        while (n > 0)
        {
            Node *p1 = q1.front();
            q1.pop();
            if (p1->file_number == number1)
            {
                if (p1->type == "Folder")
                {
                    p1->size += size1;
                    // new node function should be below.
                    (p1->child).push_back(newNode(number, name1, size1, type1));
                    //cout<<"Showing the tree:\n";
                    //LevelOrderTraversal(root);
                    cout << "\nnode moved\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
                else
                {
                    cout << "\n\t\t\t***ERROR***";
                    cout << "\nThe given file type is not a folder so it will not take another file as its child\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
            }
            for (i = 0; i < p1->child.size(); i++)
                q1.push(p1->child[i]);
            n--;
        }
    }
}

void Modify_node_details(Node *root)
{
    cout << "\n--------------------------------------------------\n";
    cout << "\n\t\t\t***Details Modifying***\n";
    int number, i,n,new_file_number;
    string new_name;
    cout << "\nEnter what file/folder to modify details\n";
    cin >> number;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        n = q.size();
        while (n > 0)
        {
            Node *p = q.front();
            q.pop();
            if (p->file_number == number)
            {
                if (p->file_number == 1 || p->file_number == 2 || p->file_number == 3 || p->file_number == 4)
                {
                    cout << "\n\t\t\t***ERROR***";
                    cout << "\nGiven file is a main directory and modifying the details is not possible\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
                else
                {
                    cout << "\nGiven file number: " << p->file_number;
                    cout << "\nEnter new file number: ";
                    cin >> new_file_number;
                    p->file_number = new_file_number;
                    cout << "\nGiven name: " << p->name;
                    cout << "\nEnter new name: ";
                    cin.ignore();
                    getline(cin, new_name);
                    p->name = new_name;
                    cout << "\nModifying Complete!\n";
                    cout << "\n--------------------------------------------------\n";
                    return;
                }
            }
            for (i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
    }
}

// Driver program
int main()
{
    //main directories that should be present in the tree initially.
    Node *root = newNode(0, "Root", 0.0, "Folder");
    (root->child).push_back(newNode(1, "Download", 0.0, "Folder"));
    (root->child).push_back(newNode(2, "Desktop", 0.0, "Folder"));
    (root->child).push_back(newNode(3, "Pictures", 0.0, "Folder"));
    (root->child).push_back(newNode(4, "Documents", 0.0, "Folder"));

    cout << "\n\t\t\t\t\t***Welcome***\n";
    cout << "A file system with Built-in Directories(Download,desktop,Pictures,Documents) already created";
    int choice;
    while (choice != 6)
    {
        cout << "\n--------------------------------------------------\n";
        cout << "\nEnter what you would like to perform:";
        cout << "\n1.Insert a new file/folder";
        cout << "\n2.Delete an existing file/folder";
        cout << "\n3.Modify an existing file/folder position";
        cout << "\n4.Modify an existing file/folder details";
        cout << "\n5.View all files";
        cout << "\n6.Exit application and delete inputed data\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nPerforming INSERTION:\n";
            Insert_Node(root);
            break;

        case 2:
            cout << "\nPerforming DELETION:\n";
            cout << "\n--------------------------------------------------\n";
            cout << "\n\t\t\t***DELETION***\n";
            cout << "\nEnter what file/folder to delete(enter file number): ";
            int number;
            cin >> number;
            Delete_Node(root, number);
            break;
        case 3:
            cout << "\nModifying file location:\n";
            Modify_node_position(root);
            break;
        case 4:
            cout << "\nModifying file details:\n";
            Modify_node_details(root);
            break;

        case 5:
            cout << "\nViewing files:\n";
            Traversal(root);
            break;

        case 6:
            cout << "\nExiting Application\n";
            exit(0);
            break;
        default:
            cout << "\nEnter Valid option\n";
        }
    }
    return 0;
}
