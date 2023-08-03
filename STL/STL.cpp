#include<iostream>
using namespace std;

template <class T>

struct NodeS{
    T data ;
    struct NodeS * next ;
};

/////////////////////////////////////////////////////////////////////////////////
// Class of Singly Linear Link list
/////////////////////////////////////////////////////////////////////////////////
template <class T>
class SinglyLL{
        public:
        //Characteristic
        NodeS<T> *Head;
        int count ;

        //Function
        SinglyLL();
        void Display();
        int Count();

        void InsertFirst(T);
        void InsertLast(T);
        void InsertAtPos(T no, int pos);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int pos);
};

template <class T>
SinglyLL <T>:: SinglyLL()
{
    Head = NULL;
    count = 0;
}

template <class T>
void SinglyLL <T> :: Display()
{
    if(Head == NULL)
    {
        cout<<"Link list is empty";
    }
    NodeS<T> * temp = Head;

    while(temp != NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }cout<<"NULL";
}

template <class T>
int SinglyLL <T>:: Count()
{
    return count;
}

template <class T>
void SinglyLL <T>:: InsertFirst(T no)
{
    //Allocation of memory
    NodeS <T> * newn = new NodeS<T>;

    //Allocate the member 
    newn->data = no;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn;
    }else{
        newn->next = Head;
        Head = newn;
    }
    count++;
}


template <class T>
void SinglyLL <T>:: InsertLast(T no)
{
    //Allocate the memory
   NodeS<T> * newn = new NodeS<T>;

    //Allocate the memnbers
    newn->data = no;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn;
    }else{
        NodeS <T> * temp = Head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;
    }
    count++;
}

template <class T>
void SinglyLL <T> :: DeleteFirst()
{
    if(Head == NULL)
    {
        return ;
    }else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }else{
        NodeS <T> *temp = Head;
        Head = Head->next;
        delete temp;
    }
    
    count--;
}
template <class T>
void SinglyLL<T> :: DeleteLast()
{
    if(Head == NULL)
    {
        return ;
    }else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }else{
        NodeS <T> *temp = Head;

        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    count--;
}

template <class T>
void SinglyLL <T>:: InsertAtPos(T no , int ipos)
{
    int icoutn = Count();
    
    if((ipos < 1) || (ipos > (icoutn + 1)))
    {
        return ;
    }

    if(ipos == 1)
    {
        InsertFirst( no);
    }else if(ipos == icoutn + 1)
    {
        InsertLast(no);
    }else{
        NodeS <T>* newn = new NodeS<T>;
        newn->data = no;
        newn->next = NULL;
        NodeS <T> *temp = Head; 
        
        for(int i = 1; i < (ipos - 1) ; i++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next = newn;
        icoutn++;
    }
    
} 

template <class T>
void SinglyLL <T> :: DeleteAtPos(int pos)
{
    int icounter = Count();
    if((pos < 1) || (pos > icounter))
    {
        return ;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }else if(pos == icounter)
    {
        DeleteLast();
    }else{
        NodeS <T> *temp = Head;

        for(int i = 1; i < (pos - 1) ; i++)
        {
            temp = temp->next;
        }
        NodeS <T> * tempX = temp->next;
        temp->next = temp->next->next;
        delete tempX;
        icounter--;
    }
    
}

/////////////////////////////////////////////////////////////////////////////////
// Class of Singly Linear Circular list
/////////////////////////////////////////////////////////////////////////////////

// template <class T>

// struct NodeS{
//     T data ;
//     struct NodeS * next ;
// };
template <class T>
class SinglyCL{
    public:
    //characterstic
    NodeS <T> * Head ;
    NodeS <T> * Tail ;
    int icount ;


    //function
    SinglyCL();
    void Display();
    int Count();

    void InsertFirst(T);
    void InsertLast(T);
    void InsertAtPos(T , int pos);
    
    void DeleteFirst();
    void DeleteLast();
    void DeleteAtPos(int pos);

};

template <class T>
SinglyCL <T> :: SinglyCL()
{
    Head = NULL;
    Tail = NULL;
    icount = 0;
}

template <class T>
void SinglyCL <T> :: Display()
{
    struct NodeS <T> * temp = Head;
    do
    {
        cout<<"|"<<temp->data<<"|=>";
        temp = temp->next;
    }while(temp  != Head);
    
}
template <class T>
int SinglyCL <T> :: Count()
{
    int total = 0;
    struct NodeS <T> * temp = Head;
    do
    {
        total++;
        temp = temp->next;
    }while(temp  != Head);
    return total;
}

template <class T>
void SinglyCL <T> :: InsertFirst(T no)
{
    NodeS <T> * newn = new NodeS<T>;

    newn->data = no;
    newn->next = NULL;
    
    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;

    }else{
        //link the next part of newn node with Head
        newn->next = Head;
        Head = newn;

    }
    
    Tail->next = Head;
}

template <class T>
void SinglyCL <T> ::InsertLast(T no)
{
    //Allocate the memory
    NodeS <T> *newn = new NodeS<T>;

    //Inilize the member
    newn->data = no;
    newn->next = NULL; 

    //Allocte the Node at appropritate position
    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;
    }else{
        Tail->next = newn;
        newn->next = Head;

        Tail = Tail->next;
    }
    Tail->next = Head;
 
}

template <class T>
void SinglyCL <T> :: DeleteFirst()
{
    if((Head == NULL) || (Tail == NULL))
    {
        return;
    }else if(Head->next == Head)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }else{
        Head = Head->next;
        delete Tail->next;

        Tail->next = Head;
    }
}

template <class T>
void SinglyCL <T> :: DeleteLast()
{
    if((Head == NULL) || (Tail == NULL))
    {
        return;
    }else if(Head->next == Head)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }else{
        NodeS <T> * temp = Head;

        do
        {
            temp = temp->next;
        }while(temp->next->next != Head);


        delete temp->next;
        Tail = temp;
        Tail->next = Head;
    }
}

template <class T>
void SinglyCL <T> :: InsertAtPos(T no , int pos)
{
    int count = Count();

    if((pos < 1) || (pos > (count + 1)))
    {
        return ;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }else if(pos == (count + 1))
    {
        InsertLast(no);
    }else{
        //Allocate the memory
        struct NodeS <T> * newn = new NodeS<T>;
        //Inilize the members 
        newn->data = no;
        newn->next = NULL;


        //create the node to travel the list
        struct NodeS <T> * temp = Head;
        for(int i = 1 ; i < (pos - 1) ; i++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next = newn;       

    }
}

template <class T>
void SinglyCL <T> :: DeleteAtPos(int pos)
{
    int icount = Count();

    if((pos < 1 ) || (pos > icount))
    {
        return ;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }else if(pos == icount)
    {
        DeleteLast();
    }else{
        //To reach that we need pointer
        struct NodeS <T> * temp = Head;

        for(int i = 1 ; i < (pos - 1) ; i++)
        {
            temp = temp->next;
        }
        //to hold the addres the node that we want to delet we need pointer
        struct NodeS <T> * tempX = temp->next;

        temp->next = temp->next->next;
        delete tempX;
    }
}
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// Class of Doubly Linear list
/////////////////////////////////////////////////////////////////////////////////
template <class T>
struct NodeD{
    T data ;
    struct NodeD * next ;
    struct NodeD * prev ;
};

template <class T>
class DoublyLL
{
    public:
        //characteristic
        struct NodeD<T> * Head;
        int count ;

        //function
        DoublyLL();
        void Display();
        void DisplayR();
        int countX();

        void InsertFirst(T);
        void InsertLast(T);
        void InsertAtPos(T , int ipos);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int pos);

};

template <class T>
DoublyLL<T> :: DoublyLL()
{
    Head = NULL;
    count = 0;
}

template <class T>
void DoublyLL<T> :: Display()
{
    
    NodeD <T> * temp = Head;
    while(temp!= NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }cout<<"NULL";
}

template <class T>
void DoublyLL<T> :: DisplayR()
{
    
    NodeD <T> * temp = Head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    while(temp!= NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->prev;
    }cout<<"NULL";
}


template <class T>
int DoublyLL<T> :: countX()
{
    return count;
}


template <class T>
void DoublyLL<T> :: InsertFirst(T no)
{
    struct NodeD<T> *newn = new NodeD<T>;
    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;
    
    if(Head == NULL)
    {
        Head = newn;
        count++;
        return ;
    }else{
        newn->next = Head;
        newn->next->prev = newn;

        Head = newn;
    }
    count++;
}

template <class T>
void DoublyLL<T> :: InsertLast(T no)
{
    NodeD <T> * newn = new NodeD<T>;
    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if(Head == NULL)
    {
        Head = newn;
        count++;
        return ;
    }else{
        struct NodeD <T> * temp = Head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        } 
        temp->next = newn;
        newn->prev = temp;
    }
    count++;
}

template <class T>
void DoublyLL<T>:: InsertAtPos(T no , int pos)
{
    int icount = countX();

    if((icount < 1 ) || (icount > (icount + 1)))
    {
        return ;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }else if(pos == (icount + 1))
    {
        InsertLast(no);   
    }else{
        struct NodeD <T> * newn = new NodeD<T>;
        newn->data = no;
        newn->next = NULL;
        newn->prev = NULL;

        struct NodeD <T> * temp = Head;
        for(int i = 1 ; i < (pos - 1) ; i++)
        {
            temp = temp->next;
        }

        //right linkage
        newn->next = temp->next;
        temp->next->prev = newn;

        //left linkage
        newn->prev = temp;
        temp->next = newn;

    }

}

template <class T>
void DoublyLL<T> :: DeleteFirst()
{
    
    if(Head == NULL)
    {
        return ;
    }
    
    if(Head->next == NULL)
    {
        //delete Head->next;
        delete Head;
        Head = NULL;
        count--;
        return ;
    }else{
        Head = Head->next;
        delete Head->prev;

        Head->prev = NULL;
    }
    count--;
}

template <class T>
void DoublyLL<T> :: DeleteLast()
{
    if(Head == NULL)
    {
        return ;
    }

    if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }else{
        struct NodeD<T> * temp = Head;

        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
}



template <class T>
void DoublyLL<T> :: DeleteAtPos(int pos)
{
    int count = countX();

    if((pos < 1) || (pos > count))
    {
        return ;
    }
    if(pos == 1)
    {
        DeleteFirst();
    }else if(pos == count)
    {
        DeleteLast();
    }else{
        struct NodeD <T> * temp = Head;
        for(int i = 1; i < (pos - 1); i++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete temp->next->prev;
        temp->next->prev = temp;
    }
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Class of Doubly Circular list
/////////////////////////////////////////////////////////////////////////////////
// template <class T>
// struct NodeD{
//     T data ;
//     struct NodeD * next ;
//     struct NodeD * prev ;
// };
template <class T>
class DoublyCL{
    public:
    int count ;
    NodeD <T> *Head ;
    NodeD <T> *Tail ;
    

    //Function
    DoublyCL();
    void Display();
    void DisplayR();
    int COUNT();

    void InsertFirst(T);
    void InsertLast(T);
    void InsertAtPos(T , int pos);

    void DeleteFirst();
    void DeleteLast();
    void DeleteAtpos(int pos);
};

template <class T>
DoublyCL<T> :: DoublyCL()
{
    Head = NULL;
    Tail = NULL;
    count = 0;
}

template <class T>
int DoublyCL<T> :: COUNT()
{
    int count = 0;
    struct NodeD <T> * temp = Head;
    do
    {   
        count++;
        temp = temp->next;
    }while(temp != Head);
    return count;
}

//Display the Link list 
template <class T>
void DoublyCL <T> :: Display()
{
    struct NodeD <T> * temp = Head;
    do
    {   
        cout<<"|"<<temp->data<<"|=>";
        temp = temp->next;
    }while(temp != Head);
}

//Display the link list in reverse order
template <class T>
void DoublyCL <T> :: DisplayR()
{
    struct NodeD <T> * temp = Head;
    while(temp->next != Head)
    {
        temp = temp->next;
    }
    do
    {   
        cout<<"|"<<temp->data<<"|=>";
        temp = temp->prev;
    }while(temp != Tail);
}

template <class T>
void DoublyCL <T> :: InsertFirst(T no )
{
    //Allocate the memory 
    struct NodeD<T> *newn = new NodeD<T>;

    //Inilize the members 
    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;
    
    //store at appropriate position
    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;

        Tail->next = Head;
        Head->prev = Tail;
    }else{
        //right linkage
        newn->next = Head;
        Head->prev = newn;

        //left linkage
        Head = newn;
        newn->prev = Tail;
        Tail->next = Head;
    }
}

template <class T>
void DoublyCL<T> :: InsertLast(T no)
{
    //Allocate the memeory
    struct NodeD<T> * newn = new NodeD<T>;

    //Inilize the members
    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;
        Tail->next = Head;
        Head->prev = Tail;
    }else{
        //Right linkage
        newn->next = Head;
        Head->prev = newn;

        //left linkage
        Tail->next = newn;
        newn->prev = Tail;

        //Move the tail by one
        Tail = Tail->next;        
    }
}

template <class T>
void DoublyCL<T> :: DeleteFirst()
{
    if((Head == NULL) || (Tail == NULL))
    {
        return;
    }else if((Head->next == Head ) && (Tail->prev == Tail))
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }else{
        //moving the Head to Head->next position
        Head = Head->next;
        //setting the Head->prev position to Tail
        Head->prev = Tail;
        //Delete the node the address of that node was held by Tail->next 
        delete Tail->next;
        //Settign the Tail->next to Head;
        Tail->next = Head;
    }

}

template <class T>
void DoublyCL<T> :: DeleteLast()
{
    if((Head == NULL) || (Tail == NULL))
    {
        return;
    }else if((Head->next == Head ) && (Tail->prev == Tail))
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }else{
        //move the Tail to its previous not because we have to delete the last node
        Tail = Tail->prev;
        //Delete the Tail->next
        delete Tail->next;
        //set the value of Tail->next = Head;
        Tail->next = Head;
        //set the value of Head->prev = Tail;
        Head->prev = Tail;
    }
}

template <class T>
void DoublyCL <T> :: InsertAtPos(T no , int pos )
{
    int icount = COUNT();

    if((pos < 1 ) || (pos > (icount + 1)))
    {
        return;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }else if (pos == (icount + 1))
    {
        InsertLast(no);
    }else{
        //Allocate the memory
        struct NodeD <T> * newn = new NodeD<T>;

        //Inilize the members
        newn->next = NULL;
        newn->prev = NULL;
        newn->data = no;

        struct NodeD<T> *temp = Head;
        for(int i = 1 ;i < (pos -1 ) ; i++)
        {
            temp = temp->next;
        }
        //Right linkage
        newn->next = temp->next;
        temp->next->prev = newn;

        //Left Linkage
        temp->next = newn;
        newn->prev = temp;
    }
}

template <class T>
void DoublyCL <T> ::DeleteAtpos(  int pos )
{
    int icount = COUNT();

    if((pos < 1 ) || (pos > (icount )))
    {
        return;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }else if (pos == icount)
    {
        DeleteLast();
    }else{
        //TO travel the linked list we need temp pointer
        struct NodeD<T> *temp = Head;
        for(int i = 1 ;i < (pos -1 ) ; i++)
        {
            temp = temp->next;
        }
        //move the temp 
        temp->next = temp->next->next;
        //delete the node
        delete temp->next->prev;
        temp->next->prev = temp;    
    }
}
/////////////////////////////////////////////////////////////////////////////////
int main()
{
    int choice = 0;
    int value = 0;
    int pos = 0;
    char ch = '\0';

    SinglyLL <char> obj;
    SinglyLL <int> obj1;
    SinglyLL <double> obj2;

    while(1)
    {
        cout<<"\n \t For which Data you want Linked List";
        cout<<"\n \t 1) Character ";
        cout<<"\n \t 2) Integer ";
        cout<<"\n \t 3) double";
        cout<<"\n \t Enter your choice :";
        cin>>choice;
        switch(choice)
        {
            case 1: 
                    while(1)
                    {
                        cout<<"\n \t 1)Insert First ";
                        cout<<"\n \t 2)Insert Last ";
                        cout<<"\n \t 3)Insert At pos ";
                        cout<<"\n \t 4)Delete First ";
                        cout<<"\n \t 5)Delete Last ";
                        cout<<"\n \t 6)Delete At pos ";
                        cout<<"\n \t 7) Count ";
                        cout<<"\n \t 8) Display";
                        cout<<"\n \t 9) Exit";
                        cout<<"\n\tEnter your choice :";
                        cin>>choice;

                        switch(choice)
                        {
                            case 1 : cout<<"\n \t Insert First ";
                                    cout<<"\n\t Enter the Element :";
                                    cin>> ch;
                                    obj.InsertFirst(ch);
                                    break;

                            case 2 : cout<<"\n \t Insert Last ";
                                    cout<<"\n\t Enter the Element :";
                                    cin>> ch;
                                    obj.InsertLast(ch);
                                    break;

                            case 3 : cout<<"\n \t Insert At pos ";
                                    cout<<"\n\t Enter the Element :";
                                    cin>> ch;
                                    cout<<"\n \t Enter the position :";
                                    cin>>pos;
                                    obj.InsertAtPos(ch , pos);
                                    break;                    

                            case 4 : cout<<"\n \t Delete First ";
                                    obj.DeleteFirst();
                                    cout<<"\n\t Element Deleted succesfully... ";
                                    break;
                                    
                            case 5 :cout<<"\n \t Delete Last ";
                                    obj.DeleteLast();
                                    cout<<"\n\t Element Deleted succesfully... ";
                                    break;
                                    
                            case 6 : cout<<"\n \t Delete At pos ";
                                    cout<<"\n \t Enter the position :";
                                    cin>>pos;
                                    obj.DeleteAtPos(pos);
                                    cout<<"\n\t Element Deleted succesfully... ";
                                    break;
                                    
                            case 7 :cout<<"\n \t  Count ";
                                    cout<<"\n \tTotal no Nodes is :"<<obj.Count();
                                    break;
                            
                            case 8 : cout<<"\n \t  Display";
                                    cout<<"\n \t Elements are  :";
                                    obj.Display();
                                    break;

                            case 9 : cout<<"\n \t  Exit";
                                    cout<<"Thanks for using this applicatoin ...";
                                    exit(0);
                    }
                        
                    }
                    break;
            case 2: 
                    cout<<"\n \t 1)Insert First ";
                    cout<<"\n \t 2)Insert Last ";
                    cout<<"\n \t 3)Insert At pos ";
                    cout<<"\n \t 4)Delete First ";
                    cout<<"\n \t 5)Delete Last ";
                    cout<<"\n \t 6)Delete At pos ";
                    cout<<"\n \t 7) Count ";
                    cout<<"\n \t 8) Display";
                    cout<<"\n \t 9) Exit";
                    cout<<"\n\tEnter your choice :";
                    cin>>choice;

                    switch(choice)
                    {
                        case 1 : cout<<"\n \t Insert First ";
                                cout<<"\n\t Enter the Element :";
                                cin>> value;
                                obj1.InsertFirst(value);
                                break;

                        case 2 : cout<<"\n \t Insert Last ";
                                cout<<"\n\t Enter the Element :";
                                cin>> value;
                                obj1.InsertLast(value);
                                break;

                        case 3 : cout<<"\n \t Insert At pos ";
                                cout<<"\n\t Enter the Element :";
                                cin>> value;
                                cout<<"\n \t Enter the position :";
                                cin>>pos;
                                obj1.InsertAtPos(value , pos);
                                break;                    

                        case 4 : cout<<"\n \t Delete First ";
                                obj1.DeleteFirst();
                                cout<<"\n\t Element Deleted succesfully... ";
                                break;
                                
                        case 5 :cout<<"\n \t Delete Last ";
                                obj1.DeleteLast();
                                cout<<"\n\t Element Deleted succesfully... ";
                                break;
                                
                        case 6 : cout<<"\n \t Delete At pos ";
                                cout<<"\n \t Enter the position :";
                                cin>>pos;
                                obj1.DeleteAtPos(pos);
                                cout<<"\n\t Element Deleted succesfully... ";
                                break;
                                
                        case 7 :cout<<"\n \t  Count ";
                                cout<<"\n \tTotal no Nodes is :"<<obj1.Count();
                                break;
                        
                        case 8 : cout<<"\n \t  Display";
                                cout<<"\n \t Elements are  :";
                                obj1.Display();
                                break;

                        case 9 : cout<<"\n \t  Exit";
                                cout<<"Thanks for using this applicatoin ...";
                                exit(0);
                        
                    }
                    break;
            case 3: 
                                cout<<"\n \t 1)Insert First ";
                                cout<<"\n \t 2)Insert Last ";
                                cout<<"\n \t 3)Insert At pos ";
                                cout<<"\n \t 4)Delete First ";
                                cout<<"\n \t 5)Delete Last ";
                                cout<<"\n \t 6)Delete At pos ";
                                cout<<"\n \t 7) Count ";
                                cout<<"\n \t 8) Display";
                                cout<<"\n \t 9) Exit";
                                cout<<"\n\tEnter your choice :";
                                cin>>choice;

                                switch(choice)
                                {
                                    case 1 : cout<<"\n \t Insert First ";
                                            cout<<"\n\t Enter the Element :";
                                            cin>> value;
                                            obj2.InsertFirst(value);
                                            break;

                                    case 2 : cout<<"\n \t Insert Last ";
                                            cout<<"\n\t Enter the Element :";
                                            cin>> value;
                                            obj2.InsertLast(value);
                                            break;

                                    case 3 : cout<<"\n \t Insert At pos ";
                                            cout<<"\n\t Enter the Element :";
                                            cin>> value;
                                            cout<<"\n \t Enter the position :";
                                            cin>>pos;
                                            obj2.InsertAtPos(value , pos);
                                            break;                    

                                    case 4 : cout<<"\n \t Delete First ";
                                            obj2.DeleteFirst();
                                            cout<<"\n\t Element Deleted succesfully... ";
                                            break;
                                            
                                    case 5 :cout<<"\n \t Delete Last ";
                                            obj2.DeleteLast();
                                            cout<<"\n\t Element Deleted succesfully... ";
                                            break;
                                            
                                    case 6 : cout<<"\n \t Delete At pos ";
                                            cout<<"\n \t Enter the position :";
                                            cin>>pos;
                                            obj2.DeleteAtPos(pos);
                                            cout<<"\n\t Element Deleted succesfully... ";
                                            break;
                                            
                                    case 7 :cout<<"\n \t  Count ";
                                            cout<<"\n \tTotal no Nodes is :"<<obj2.Count();
                                            break;
                                    
                                    case 8 : cout<<"\n \t  Display";
                                            cout<<"\n \t Elements are  :";
                                            obj2.Display();
                                            break;

                                    case 9 : cout<<"\n \t  Exit";
                                            cout<<"Thanks for using this applicatoin ...";
                                            exit(0);
                                    
                                }
                                break;
                    break;
            case 4: cout<<"\n\t Thanks for using this application ...";
                    exit(0);       
        }
        /*cout<<"\n \t 1)Insert First ";
        cout<<"\n \t 2)Insert Last ";
        cout<<"\n \t 3)Insert At pos ";
        cout<<"\n \t 4)Delete First ";
        cout<<"\n \t 5)Delete Last ";
        cout<<"\n \t 6)Delete At pos ";
        cout<<"\n \t 7) Count ";
        cout<<"\n \t 8) Display";
        cout<<"\n \t 9) Exit";
        cout<<"\n\tEnter your choice :";
        cin>>choice;

        switch(choice)
        {
            case 1 : cout<<"\n \t Insert First ";
                     cout<<"\n\t Enter the Element :";
                     cin>> value;
                     obj.InsertFirst(value);
                     break;

            case 2 : cout<<"\n \t Insert Last ";
                     cout<<"\n\t Enter the Element :";
                     cin>> value;
                     obj.InsertLast(value);
                     break;

            case 3 : cout<<"\n \t Insert At pos ";
                     cout<<"\n\t Enter the Element :";
                     cin>> value;
                     cout<<"\n \t Enter the position :";
                     cin>>pos;
                     obj.InsertAtPos(value , pos);
                    break;                    

            case 4 : cout<<"\n \t Delete First ";
                     obj.DeleteFirst();
                    cout<<"\n\t Element Deleted succesfully... ";
                    break;
                    
            case 5 :cout<<"\n \t Delete Last ";
                     obj.DeleteLast();
                    cout<<"\n\t Element Deleted succesfully... ";
                    break;
                     
            case 6 : cout<<"\n \t Delete At pos ";
                     cout<<"\n \t Enter the position :";
                     cin>>pos;
                     obj.DeleteAtPos(pos);
                     cout<<"\n\t Element Deleted succesfully... ";
                     break;
                    
            case 7 :cout<<"\n \t  Count ";
                     cout<<"\n \tTotal no Nodes is :"<<obj.Count();
                     break;
            
            case 8 : cout<<"\n \t  Display";
                     cout<<"\n \t Elements are  :";
                     obj.Display();
                     break;

            case 9 : cout<<"\n \t  Exit";
                     cout<<"Thanks for using this applicatoin ...";
                    exit(0);
            
        }*/
        
    }    


    return 0;
}





