#include <iostream>
#include <string>
using namespace std;

struct readyQueue //The ready queue - stores processes that are in the ready queue
{
	int cpuBurst;
	int processNumber;
	readyQueue* next;
};

struct ioList //List of all the process in io mode
{
	int ioBurst;
	int processNumber;
	ioList* next;
};

//Inserts a process into the back of the ready queue
void RQInsert(readyQueue** node, int cpuB, int pNum)	
{
	readyQueue* front = *node;
	readyQueue* newNode = new readyQueue;
	newNode->processNumber = pNum;
	newNode->cpuBurst = cpuB;
	newNode->next = NULL;
	if (*node == 0)
	{
		*node = newNode;
		return;
	}
	while (front->next != 0)
		front = front->next;
	front->next = newNode;
}


//Displays the processes currently in the ready queue
void RQdisplay(readyQueue* node)
{
	if (!node)
		cout << "Empty\n";
	readyQueue* newNode = node;
	while (newNode != NULL)
	{
		cout << "P" << newNode->processNumber << '|' << "CPU Burst " << newNode->cpuBurst << '\n';
		newNode = newNode->next;
	}
}

//Removes the process at the head of the ready queue and makes the next process the new head of the ready queue
void RQremove(readyQueue** node)//Deletes the first node of the linked list
{
	if (*node == NULL)  //If the head node is NULL the list is empty, this prevents there from being an error
	{
		return; //Necessary functional component
	}
	readyQueue* temp = new readyQueue;
	temp = *node;
	*node = (*node)->next;
	delete temp;
}

//Bubble sorts the processes in readyQueue by their ioBurst value in increasing order
void RQSort(readyQueue** snode)
{
	readyQueue* trav = *snode;
	int tempioBurst; //an integer used to store the contents of cpuBurst, while the contents of cpuBurst are replaced with that of the node with a lower value
	int tempProcess; //an integer used to store a process number
	int counter = 0;
	while (trav != NULL)
	{
		trav = trav->next;
		counter++;
	}
	trav = *snode;
	for (int i = 0; i < counter - 1; i++) //the bubble sort algorithm implemented here only needs to occur: number of cpuBursts to sort - 1 times
	{
		while (trav->next != NULL) //Each iteration of this while function bubbles the highest value starting from the front of the list to the back of the list
		{
			if (trav->cpuBurst > (trav->next)->cpuBurst)
			{
				tempioBurst = trav->cpuBurst;	//the value of cpuBurst in the current node is temporarily stored in tempioBurst
				trav->cpuBurst = trav->next->cpuBurst; //the value of cpuBurst in the current node is changed to the value in the next node
				trav->next->cpuBurst = tempioBurst; //the value of cpuBurst in the next node is changed to the value that was in current node prior to its change

				tempProcess = trav->processNumber;
				trav->processNumber = trav->next->processNumber;
				trav->next->processNumber = tempProcess;

				trav = trav->next; //moving to the next node in the list
			}
			else
				trav = trav->next; //moving to the next node in the list
		}
		trav = *snode; //resetting trav to start from start of linked list
	}
}

//Inserts a process and its IO Burst amount at the end of the linked list of processes in IO burst mode
void ioListInsert(ioList** node, int ioB, int ipNum)
{
	ioList* temp = *node;	//front turn into temp
	ioList* newNode = new ioList();
	newNode->ioBurst = ioB;
	newNode->processNumber = ipNum;
	newNode->next = NULL;
	if (*node == 0)
	{
		*node = newNode;
		return;
	}
	while (temp->next != 0)
		temp = temp->next;
	temp->next = newNode;
}

//Prints all processes currently using IO devices/ in IO burst mode and their respective remaining Io burst time before entering the ready queue
void ILdisplay(ioList* node)
{
	if (!node)
		cout << "Empty\n";
	ioList* newNode = node;
	while (newNode != NULL)
	{
		cout << "P" << newNode->processNumber << '|' << "IO Burst " << newNode->ioBurst << '\n';
		newNode = newNode->next;
	}
}

//Removes the first node of the ioList
void ILremove(ioList** node)//Deletes the first node of the linked list
{
	if (*node == NULL)  //If the head node is NULL the list is empty, this prevents there from being an error
	{
		return; //does not remove a node if the list is empty
	}
	ioList* temp = new ioList;
	temp = *node;
	*node = (*node)->next;
	delete temp;
}

//Bubble sorts the processes in ioList by their ioBurst value in increasing order
void ILSort(ioList** snode) 
{
	ioList* trav = *snode;
	int tempioBurst; //an integer used to store the contents of ioBurst, while the contents of ioBurst are replaced with that of the node with a lower value
	int tempProcess; //an integer used to store a process number
	int counter = 0;
	while (trav != NULL)
	{
		trav = trav->next;
		counter++;
	}
	trav = *snode;
	for (int i = 0; i < counter - 1; i++) //the bubble sort algorithm implemented here only needs to occur: number of ioBursts to sort - 1 times
	{
		while (trav->next != NULL) //Each iteration of this while function bubbles the highest value starting from the front of the list to the back of the list
		{
			if (trav->ioBurst > (trav->next)->ioBurst)
			{
				tempioBurst = trav->ioBurst;	//the value of ioBurst in the current node is temporarily stored in tempioBurst
				trav->ioBurst = trav->next->ioBurst; //the value of ioBurst in the current node is changed to the value in the next node
				trav->next->ioBurst = tempioBurst; //the value of ioBurst in the next node is changed to the value that was in current node prior to its change

				tempProcess = trav->processNumber;
				trav->processNumber = trav->next->processNumber;
				trav->next->processNumber = tempProcess;

				trav = trav->next; //moving to the next node in the list
			}
			else
				trav = trav->next; //moving to the next node in the list
		}
		trav = *snode; //resetting trav to start from start of linked list
	}
}

//Calculates and returns the sum of all processes's CPU bursts
int sumCPUBurst(int CB[][10])
{
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sum += CB[i][j]; 
		}
	}
	return sum;
}

//Traverses the array of CPU bursts and returns the next nonzero cpu burst to occur for a particular process
int getCBurst(int pNum, int CB[][10])
{
	for (int i = 0; i < 10; i++)
	{
		if (CB[pNum - 1][i] > 0)
		{
			int burst = CB[pNum - 1][i];	//temporarily stores the cpu burst of the process
			CB[pNum - 1][i] = 0;	//sets the value of the cpu burst to 0
			return burst;	//return the stored nonzero value of the cpu burst of the process
		}
	}
}

//Traverses the array of io bursts and returns the next nonzero io burst to occur for a particular process
int getIBurst(int pNum, int IB[][10])
{
	for (int i = 0; i < 10; i++)
	{
		if (IB[pNum - 1][i] > 0)
		{
			int burst = IB[pNum - 1][i];	//temporarily stores the io burst of the process
			IB[pNum - 1][i] = 0;	//sets the value of the io burst to 0
			return burst;	//return the stored nonzero value of the io burst of the process
		}
	}
}

//Reduces the ioBurst of each process in the ioList by 1 and sends any process whose ioBurst becomes 0 to the readyQueue with their next cpuBurst value
void ioDecrement(ioList* node, int CB[][10], readyQueue* rnode)
{
	while(1)//do//while (node->next != NULL)
	{
		node->ioBurst--;
		if (node->ioBurst == 0)
		{
			int currentCBurst = getCBurst(node->processNumber, CB);
			RQInsert(&rnode, currentCBurst, node->processNumber);
			ILremove(&node);
		}
		if (node->next)
			node = node->next;
		else if (node->next == NULL)
			break;

	} 
}

//Displays whether the running process or "None" to describe the running state process if there isn't one
string RPdisplay(int runningProcess)
{
	if (!runningProcess)
		return "None";
	else
	{
		string s = to_string(runningProcess);
		return "P" + s;
	}
}

//Carries out process scheduling with FCFS as the scheduling algorithm
void FCFS(int nCB[][10], int nIB[][10], int CB[][10], int IB[][10])
{
	cout << "~~~~~~~~~~~~~~~~Executing: FCFS Scheduling Algorithm~~~~~~~~~~~~~~~~~~";	//Printing title of algorithm
	int CET = 0;	//Current Execution Time
	readyQueue* head = NULL;
	ioList* front = NULL;
	int cpuB;
	int pNum;	
	int runningProcess = 0;
	int runningCBurst = 0;
	for (int i = 0; i < 8; i++)	//inserting all 8 of processes into the ready queue with their initial CPU burst value 
	{
		cpuB = CB[i][0];
		pNum = i + 1;
		RQInsert(&head, cpuB, pNum);
	}
	cout << "\nCurrent execution time: " << CET << '\n' << "Running process: " << RPdisplay(runningProcess) << "\n\n" << "Ready queue: \n";
	RQdisplay(head);
	cout << "\nProcesses in I/O: \n";
	ILdisplay(front);
	CET += getCBurst(1, CB);	//CB[0][0]

	int ioB = getIBurst(1, IB); //IB[0][0]
	int ipNum = head->processNumber;
	//There should be a loop around this area to increment a variable to skim through and pick up IOBurst values
	ioListInsert(&front, ioB, ipNum);
	RQremove(&head);
	runningProcess = head->processNumber;
	runningCBurst = getCBurst(runningProcess, CB);	//CB[1][0] = 0;
	RQremove(&head);
	cout << "\nCurrent execution time: " << CET << '\n' << "Running process: " << RPdisplay(runningProcess) << "\n\n" << "Ready queue: \n";
	RQdisplay(head);
	cout << "\nProcesses in I/O: \n"; 
	ILdisplay(front);
	cout << "----------------------------FCFS Scheduling Algorithm---------------------------------\n";
	/*Enter code to indicate when a process has completed its total execution*/
	int ioDecrementValue = runningCBurst;
	while (ioDecrementValue > 0)
	{
		ioDecrement(front, CB, head);
		ioDecrementValue--;
	}
	ioB = getIBurst(runningProcess, IB);
	ioListInsert(&front, ioB, runningProcess);
	CET += runningCBurst;
	if (head)
	{
		runningProcess = head->processNumber;
		runningCBurst = getCBurst(runningProcess, CB);
	}
	else
	{
		runningProcess = NULL;
		runningCBurst = 0;
	}
	RQremove(&head);
	cout << "\nCurrent execution time: " << CET << '\n' << "Running process: " << RPdisplay(runningProcess) << "\n\n" << "Ready queue: \n";
	RQdisplay(head);
	cout << "\nProcesses in I/O: \n"; 
	ILdisplay(front);
	cout << "----------------------------FCFS Scheduling Algorithm---------------------------------\n";
	ioDecrementValue = runningCBurst;
	while (ioDecrementValue > 0)
	{
		ioDecrement(front, CB, head);
		ioDecrementValue--;
	}
	ioB = getIBurst(runningProcess, IB);
	ioListInsert(&front, ioB, runningProcess);
	CET += runningCBurst;
	if (head)
	{
		runningProcess = head->processNumber;
		runningCBurst = getCBurst(runningProcess, CB);
	}
	else
	{
		runningProcess = NULL;
		runningCBurst = 0;
	}
	RQremove(&head);
	cout << "\nCurrent execution time: " << CET << '\n' << "Running process: " << RPdisplay(runningProcess) << "\n\n" << "Ready queue: \n";
	RQdisplay(head);
	cout << "\nProcesses in I/O: \n";
	ILdisplay(front);
	cout << "----------------------------FCFS Scheduling Algorithm---------------------------------\n";
	int newioDecrementValue = 0;
	int cCBurst;
	ioDecrementValue = runningCBurst;
	while (ioDecrementValue > 0)
	{
		ioDecrement(front, CB, head);
		ioDecrementValue--;
	}
	ILSort(&front);
	newioDecrementValue = front->ioBurst;
	ioList* nNode = front;
	while (nNode)
	{
		nNode->ioBurst -= newioDecrementValue;
		nNode = nNode->next;
	}
	ioList* mNode = front;
	while (mNode)
	{
		cCBurst = 0;
		if (mNode->ioBurst == 0)
		{
			cCBurst = getCBurst(mNode->processNumber, CB);
			RQInsert(&head, cCBurst, mNode->processNumber);
		}
		if (mNode->next)
			mNode = mNode->next;
		else
			break;
	}
	//The following assumes that only one function will finish in the io list at a time, which, I understand, is not necessarily always true
	ILremove(&front);
	if(runningProcess)
	{
		ioB = getIBurst(runningProcess, IB);
		ioListInsert(&front, ioB, runningProcess);
	}
	CET += runningCBurst;
	//cout << sumCPUBurst(CB) << "\n"; this is an appropriate location to place this
	if (head)
	{
		runningProcess = head->processNumber;
		runningCBurst = getCBurst(runningProcess, CB);
		//0 - remove after, CB[0][2] starts being 0 in this block
	}
	else
	{
		runningProcess = NULL;
		runningCBurst = 0;
	}
	RQremove(&head);
	cout << "\nCurrent execution time: " << CET << '\n' << "Running process: " << RPdisplay(runningProcess) << "\n\n" << "Ready queue: \n";
	RQdisplay(head);
	cout << "\nProcesses in I/O: \n";
	ILdisplay(front);
	cout << "----------------------------FCFS Scheduling Algorithm---------------------------------\n";
	cout << "----------------------Results of FCFS Scheduling Algorithm----------------------------\n";
	//End of FCFS algorithm display
	int Tr = 0;	//Individual response time
	int totalTr = 0;	//Total response time
	cout << "Response times: ";
	for (int i = 0; i < 8; i++)
	{
		totalTr += Tr;
		cout << "\nP" << i << ": " << Tr;
		Tr += nCB[i][0];
	}
	double avTr = totalTr / 8.0;
	cout << "\nAverage Response Time: " << avTr;
}

int main()
{
	int CB[8][10]; //All CPU bursts for each process: the first index indicates the process number, the second indicates the cpu burst number(first cpu burst, 2nd, etc)
	CB[0][0] = 5; CB[0][1] = 3; CB[0][2] = 5; CB[0][3] = 4; CB[0][4] = 6; CB[0][5] = 4; CB[0][6] = 3; CB[0][7] = 4; CB[0][8] = 0; CB[0][9] = 0;
	CB[1][0] = 4; CB[1][1] = 5; CB[1][2] = 7; CB[1][3] = 12; CB[1][4] = 9; CB[1][5] = 4; CB[1][6] = 9; CB[1][7] = 7; CB[1][8] = 8; CB[1][9] = 0;
	CB[2][0] = 8; CB[2][1] = 12; CB[2][2] = 18; CB[2][3] = 14; CB[2][4] = 4; CB[2][5] = 15; CB[2][6] = 14; CB[2][7] = 5; CB[2][8] = 6; CB[2][9] = 0;
	CB[3][0] = 3; CB[3][1] = 4; CB[3][2] = 5; CB[3][3] = 3; CB[3][4] = 4; CB[3][5] = 5; CB[3][6] = 6; CB[3][7] = 5; CB[3][8] = 0; CB[3][9] = 0;
	CB[4][0] = 16; CB[4][1] = 17; CB[4][2] = 5; CB[4][3] = 16; CB[4][4] = 7; CB[4][5] = 13; CB[4][6] = 11; CB[4][7] = 6; CB[4][8] = 3; CB[4][9] = 4;
	CB[5][0] = 11; CB[5][1] = 4; CB[5][2] = 5; CB[5][3] = 6; CB[5][4] = 7; CB[5][5] = 9; CB[5][6] = 12; CB[5][7] = 15; CB[5][8] = 8; CB[5][9] = 0;
	CB[6][0] = 14; CB[6][1] = 17; CB[6][2] = 11; CB[6][3] = 15; CB[6][4] = 4; CB[6][5] = 7; CB[6][6] = 16; CB[6][7] = 10; CB[6][8] = 0; CB[6][9] = 0;
	CB[7][0] = 4; CB[7][1] = 5; CB[7][2] = 6; CB[7][3] = 14; CB[7][4] = 16; CB[7][5] = 6; CB[7][6] = 0; CB[7][7] = 0; CB[7][8] = 0; CB[7][9] = 0;

	int IB[8][10]; //All IO bursts for each process: the first index indicates the process number, the second indicates the io burst number(first io burst, 2nd, etc)
	IB[0][0] = 27; IB[0][1] = 31; IB[0][2] = 43; IB[0][3] = 18; IB[0][4] = 22; IB[0][5] = 26; IB[0][6] = 24; IB[0][7] = 0; IB[0][8] = 0; IB[0][9] = 0;
	IB[1][0] = 48; IB[1][1] = 44; IB[1][2] = 42; IB[1][3] = 37; IB[1][4] = 76; IB[1][5] = 41; IB[1][6] = 31; IB[1][7] = 43; IB[1][8] = 0; IB[1][9] = 0;
	IB[2][0] = 33; IB[2][1] = 41; IB[2][2] = 65; IB[2][3] = 21; IB[2][4] = 61; IB[2][5] = 18; IB[2][6] = 26; IB[2][7] = 31; IB[2][8] = 0; IB[2][9] = 0;
	IB[3][0] = 35; IB[3][1] = 41; IB[3][2] = 45; IB[3][3] = 51; IB[3][4] = 61; IB[3][5] = 54; IB[3][6] = 82; IB[3][7] = 77; IB[3][8] = 0; IB[3][9] = 0;
	IB[4][0] = 24; IB[4][1] = 21; IB[4][2] = 36; IB[4][3] = 26; IB[4][4] = 31; IB[4][5] = 28; IB[4][6] = 21; IB[4][7] = 13; IB[4][8] = 11; IB[4][9] = 0;
	IB[5][0] = 22; IB[5][1] = 8; IB[5][2] = 10; IB[5][3] = 12; IB[5][4] = 14; IB[5][5] = 18; IB[5][6] = 24; IB[5][7] = 30; IB[5][8] = 0; IB[5][9] = 0;
	IB[6][0] = 46; IB[6][1] = 41; IB[6][2] = 42; IB[6][3] = 21; IB[6][4] = 32; IB[6][5] = 19; IB[6][6] = 33; IB[6][7] = 0; IB[6][8] = 0; IB[6][9] = 0;
	IB[7][0] = 14; IB[7][1] = 33; IB[7][2] = 51; IB[7][3] = 73; IB[7][4] = 87; IB[7][5] = 0; IB[7][6] = 0; IB[7][7] = 0; IB[7][8] = 0; IB[7][9] = 0;

	
	//Below lies copies of the two dimensional arrays above to be used to be edited by FCFS, SJF, and MLFQ, respectively
	int FCB[8][10];
	int FIB[8][10];
	int SCB[8][10];
	int SIB[8][10];
	int MCB[8][10];
	int MIB[8][10];

	//actual copying process: storing each element of each array at the corresponding previously empty address of the copies
	for (int i = 0; i < 8; ++i) //for the first index of the two dimensional arrays
	{
		for (int j = 0; j < 10; ++j) //for the second index of the two dimensional arrays
		{
			FCB[i][j] = CB[i][j];
			FIB[i][j] = IB[i][j];
			SCB[i][j] = CB[i][j];
			SIB[i][j] = IB[i][j];
			MCB[i][j] = CB[i][j];
			MIB[i][j] = IB[i][j];
		}

	}
	FCFS(CB, IB, FCB, FIB);
}

