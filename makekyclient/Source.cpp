#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <io.h>
#include<stdio.h>
#include<WinSock2.h>
#include <string.h>
//int main() {};


void get_message_from_user(char message[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("Write your message:");
	scanf(" %[^\t\n]s", message);
}


void get_contact_type_to_show(char show_type[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("-What kind of you contact you want to see last messages:");
	scanf("%s", show_type);
}

void get_contact_name_to_show(char show_name[], char show_type[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("-Enter the name of %s you want to see last messages:", show_type);
	scanf("%s", show_name);
}

void get_new_channel_to_creagt(char channel_name[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("-Enter a name(you channel will be known as this name):");
	scanf("%s", channel_name);
}


void get_new_group_to_creat(char group_name[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("Enter a name(you group will be known as this name):");
	scanf("%s", group_name);
}
void get_the_reciever_name(char reciever_name[], char type[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("you want to send message to which %s:", type);
	scanf("%s", reciever_name);
}

void get_the_reciever_type(char type[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	printf("what kind of contact you want to chat with:");
	scanf("%s", type);

}

void get_new_contact_from_user(char new_contact[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++)printf(" ");
	printf("Enter the username to add to your contacts:");
	scanf("%s", new_contact);
	//printf("%s", new_contact);
}

void get_new_group_from_user(char new_group[]) // this is for adding a group
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++)printf(" ");
	printf("Enter the group to add to your contacts:");
	scanf("%s", new_group);
	//printf("%s", new_contact);
}



void get_new_channel_from_user(char new_channel[])
{
	system("cls");
	for (int i = 0; i < 8; i++) printf("\n");
	for (int i = 0; i < 8; i++)printf(" ");
	printf("Enter the channel to add to your contacts:");
	scanf("%s", new_channel);
	//printf("%s", new_contact);
}


void print_in_help_screen(char help[])
{
	for (int i = 0; i < 10; i++) printf(" ");
	printf("|");

	int len = strlen(help);
	int space = (100 - len) / 2;
	for (int i = 0; i < space; i++)printf(" ");
	printf("%s", help);
	printf("\n");
	printf("\n");
}

char first_what_to_do[100];
char whattodo[100];
char server_result[100];


void help_function()
{
	system("cls");
	print_in_help_screen("'add contact' ==> for adding a new username to your contact list");
	print_in_help_screen("'send message' ==> to send a massage to a group or username or channel(as a admin)");
	print_in_help_screen("'show contacts' ==> to watch you're contacts");
	print_in_help_screen("'groups' ==> to watch your joined groups");
	print_in_help_screen("'channels' ==> to see what chanels you have been joined till now");
	print_in_help_screen("'create group' ==> to create a new group in massenger");
	print_in_help_screen("'create channel' ==> to create a new channel in the massenger");
	print_in_help_screen("'join group' ==> to join a group via entering its name if it exist");
	print_in_help_screen("'join channel' ==> to join a channel via entering its name if it exist");
	print_in_help_screen("'show messages ==> to show last messages of a group , channel or pv");
	print_in_help_screen("'log out' ==> to log out from you account and program");
	
	system("pause");
}


void start_program(SOCKET connection)
{
	char server_res[50];
	recv(connection, server_res, sizeof(server_res), 0);
	char new_contact[50];
//	printf("hello world");
	//for (int i = 0; i < 1000000000; i++);
	system("cls");
	for (int i = 0; i <8; i++)printf("\n");
	for (int i = 0; i < 45; i++) printf(" ");
	
	printf("MALEKY IS LOADING...");
	for (int i = 0; i < 1000000000; i++);
	system("cls");
	scanf(" %[^\t\n]s", whattodo);
	if (strcmp(whattodo, "help") == 0)
	{
		help_function();
		start_program(connection);
	}
	else
	send(connection, whattodo, sizeof(whattodo), 0);
	//printf("hello world!\n");
	recv(connection, server_res, sizeof(server_res), 0);
//	printf("%s\n", server_res);
	if (strcmp(server_res, "send contact name") == 0)
	{
		char server_res[40];
		get_new_contact_from_user(new_contact);
		//printf("%s\n", new_contact);
		send(connection, new_contact, sizeof(new_contact), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		if (strcmp(server_res, "saved") == 0)
		{
			printf("your new contact have been saved successfully");
			system("pause");
			start_program(connection);
		}
		else
		{
			printf("There is no username such as what you enter in our server");
			system("pause");
			start_program(connection);
		}
	}
	else if (strcmp(server_res, "you wants contacts") == 0)
	{
		char all_contacts[500];
		send(connection, "yes,send it", sizeof("yes,send it"), 0);
		recv(connection, all_contacts, sizeof(all_contacts), 0);
	//	printf("%s\n", all_contacts);
		int dash_location = strlen(all_contacts) - 1;
		all_contacts[dash_location] = '\0';
		printf("%s", all_contacts);
		system("pause");
		start_program(connection);
	}
	else if (strcmp(server_res, "send reciever") == 0)
	{
		char server_res[40];
		char reciever_type[50] ;
		char reciever_name[50];
		char message[400];
		char string_to_be_send_to_server[50] = {};
		get_the_reciever_type(reciever_type);
		get_the_reciever_name(reciever_name,reciever_type );
		send(connection, reciever_name, sizeof(reciever_name), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		send(connection, reciever_type, sizeof(reciever_type), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		get_message_from_user(message);
		send(connection, message, sizeof(message), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		printf("%s\n", server_res);
		if (strcmp(server_res, "you're message have been sent") == 0)
		{
			MessageBoxA(NULL, server_res, "OK", MB_OK | MB_USERICON);
			system("cls");
			start_program(connection);
		}
		else
		{
			MessageBoxA(NULL, server_res, "Error", MB_OK | MB_ICONERROR);
			system("cls");
			start_program(connection);
		}
	}
	else if (strcmp(server_res, "send new group name") == 0) // when user wants to creat a new group .
	{
	//	printf("hello\n");
		//printf("%s\n", groups[1]);
		char server_res[50];
		char group_name[50];
		get_new_group_to_creat(group_name);
		send(connection, group_name, sizeof(group_name), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		if (strcmp(server_res, "created") == 0)
		{
			// printf("hello");
			//system("pasue");
			printf("You new group has been created!!\n");
			system("pause");
			start_program(connection);
		}
		else
		{
			printf("%s\n", server_res);
			system("pause");
			start_program(connection);
		}

	}
	else if (strcmp(server_res, "send group name" )== 0)
	{
		char group_name[50];
		char server_res[50];
		get_new_group_from_user(group_name);
		send(connection, group_name, sizeof(group_name), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		if (strcmp(server_res, "you're added") == 0)
		{
			printf("You are added to this group, now you can send message to this group\n");
			system("pause");
			start_program(connection);
		}
		else
		{
			printf("Sorry , the name that you entered is not existed or you're added before!!\n");
			system("pause");
			start_program(connection);
		}
	}
	else if (strcmp(server_res, "send new channel name") == 0)
	{
		char channel_name[50];
		char server_res[50];
		get_new_channel_to_creagt(channel_name);
		send(connection, channel_name, sizeof(channel_name), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		if (strcmp(server_res, "created") == 0)
		{
			printf("Your new channel have been created!!");
			system("pause");
			start_program(connection);
		}
		else
		{
			printf("%s\n", server_res);
			system("pause");
			start_program(connection);
		}
	}
	else if (strcmp(server_res, "send channel name") == 0)
	{
		char channel_name[50];
		char server_res[50];
		get_new_channel_from_user(channel_name);
		send(connection, channel_name, sizeof(channel_name), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		if (strcmp(server_res, "you're added") == 0)
		{
			printf("You are added to this channel, now you can see message on this channel\n");
			system("pause");
			start_program(connection);
		}
		else
		{
			printf("Sorry , the name that you entered is not existed or you're added before!!\n");
			system("pause");
			start_program(connection);
		}
	}
	else if (strcmp(server_res, "you want messages") == 0)
	
	{
		char show_type[50];
		char show_name[50];
		char server_res[50];
		char message[400];
		char server_res2[50];
		get_contact_type_to_show(show_type);
		get_contact_name_to_show(show_name, show_type);
		send(connection, show_type, sizeof(show_type), 0);
		recv(connection, server_res, sizeof(server_res), 0);
		send(connection, show_name, sizeof(show_name), 0);
		system("cls");
		while (1)
		{
			recv(connection, message, sizeof(message), 0);
			if (strcmp(message, "End") == 0)
			{
				break;
			}
			printf("%s\n", message);
			//printf("\n");
			send(connection, "send other", sizeof("send other"), 0);
		}
	//printf("ajfkalfs");
		send(connection, "showing end", sizeof("showing end"), 0);
		recv(connection, server_res2, sizeof(server_res2), 0);
		printf("%s\n", server_res2);
		system("pause");
		start_program(connection);
	}
	else if (strcmp(server_res, "log out") == 0)
	{
		send(connection, "wants to exit", sizeof("wants to exit"), 0);
		exit(0);
	}
	else if (strcmp(server_res, "you want contacts") == 0)
	{

	}
	else if (strcmp(server_res, "invalid") == 0)
	{
		printf("you have entered an invalid syntax(use 'help' to know how maleky works)\n");
		system("pause");
		start_program(connection);
	}
	
}
void sign_in(SOCKET connection)
{
	system("cls");
	char username[40];
	char password[30];
	char server_res[10];
	char another_aswer[20];
	int try_to_connect = 0;
	for (int i = 0; i < 5; i++) printf("\n");
	for (int i = 0; i < 40; i++) printf(" ");
	printf("Enter THE username :");
	scanf("%s", username);
	int success = send(connection, username, sizeof(username), 0);
	printf("\n");
	for (int i = 0; i < 40; i++) printf(" ");
	printf("Enter you password:");
	scanf("%s", password);
	if (success >= 0)
		success = send(connection, password, sizeof(password), 0);
	recv(connection, server_res, sizeof(server_res), 0);
	printf("%s\n", server_res);
	if (strcmp(server_res, "correct") == 0)
	{
		start_program(connection);
	}
	else
	{
		MessageBoxA(NULL, "You have entered an incorrect confirmation password!", "Error", MB_OK | MB_ICONERROR);
		system("cls");
		sign_in(connection);
	}	
}


void sign_up(SOCKET connection)
{
	char confirmation[50];
	char username[40];
	char password[30];
	/*recv(connection, confirmation, sizeof(confirmation), 0);
	if (strcmp(confirmation, "Send Username") == 0)
	{
		printf("I'll recieve the confirmation");
		
	}	*/
	char confirm_password[30];
	system("cls");
	for (int i = 0; i < 5; i++) printf("\n");
	for (int i = 0; i < 30; i++) printf(" ");
	printf("Enter A username :");
	scanf("%s", username);
//	printf("%s\n", username);
	send(connection, username, sizeof(username), 0);
	printf("\n");
	for (int i = 0; i < 30; i++) printf(" ");
	printf("Enter a password (max 30 character) :");
	scanf("%s", password);
	printf("\n");
	for (int i = 0; i < 30; i++) printf(" ");
	printf("Confirm the password:");
	scanf("%s", confirm_password);
	if (strcmp(password, confirm_password) == 0)
	{
		send(connection, password, sizeof(password), 0);
	}
	else
	{
		MessageBoxA(NULL, "You have entered an incorrect confirmation password!", "Error", MB_OK | MB_ICONERROR);
		system("cls");
		sign_up(connection);
	}

	system("cls");
	sign_in(connection);
}



void start_page(SOCKET connection)
{
	system("cls");
	for (int i = 0; i < 10; i++)
		printf("\n");
	printf("                                                You're connected                         \n");

	printf("                                               ___________________                     \n");
	printf("                                              |                   |                    \n");
	printf("                                              | Welcome to maleky |                    \n");
	printf("                                              |___________________|                    \n");

	printf("                                        what do you want : ");
	scanf(" %[^\t\n]s", first_what_to_do); // scan the first input that might be sing up or sing in or a nonvalid string
	send(connection, first_what_to_do, sizeof(first_what_to_do), 0); // send the massage to server
	if (strcmp(first_what_to_do, "Error") == 0)
		perror("Unvalid input");
	else if (strcmp(first_what_to_do, "sign up") == 0) sign_up(connection);
	else if (strcmp(first_what_to_do, "sign in") == 0) sign_in(connection);
	else start_page(connection);

}



int main()
{
	//windock statup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "winsock startup", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN address; // address that we will bind our listening socket to
	int addrlen = sizeof(address); // length of the address (required for accept call)
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(1111); // port to transfer
	address.sin_family = AF_INET;

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL); // set connection socket
	if (connect(connection, (SOCKADDR*)&address, sizeof(address))!= 0)
	{
		MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //failed to connect
	}
	start_page(connection);
	//char message[256];
	
	return 0;
}
