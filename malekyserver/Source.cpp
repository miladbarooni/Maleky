#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>
#include <string.h>
#include <io.h>
char whattodo[100];
char usernames[500][30];
int user_num = 0;
int number_of_user = 4;
char groups[100][50] = { "students", "principle" };
char channels[100][50];
int group_counter = 2;
int channel_counter = 0;

int is_in_users(char user[])
{
	for (int i = 0; i < number_of_user; i++)
	{
		if (strcmp(usernames[i], user) == 0)
			return 1;
	}
	return 0;
}

int is_admin_of_channel(char username[], char channel_name[])
{
	char copy_channel[50];
	strcpy(copy_channel, channel_name);
	char admin[40];
	FILE* channel = fopen(strcat(copy_channel, "_chan.txt"), "r+");
	fscanf(channel, "admin : %s", admin);
	if (strcmp(admin, username) == 0)
	{
		return 1;
	}
	return 0;
}
int is_in_channel_contact(char username[], char channel_name[])
{
	char single_username[50];
	char copy_channel[50];
	strcpy(copy_channel, channel_name);
	FILE* channel_contacts = fopen(strcat(copy_channel, "_chan_contact.txt"), "r+");
	while (fgets(single_username, 100, channel_contacts))
	{
		//printf("hello world!\n");
		int last = strlen(single_username);
		single_username[last - 1] = '\0';
		if (strcmp(single_username, username) == 0) return 1;
	}
	return 0;
}

int is_in_group_contact(char username[], char group_name[])
{
	//printf("hello");
	char single_username[50];
	char copy_group[50];
	strcpy(copy_group, group_name);
	char file_name[100];
	strcpy(file_name, strcat(copy_group, "_contacts.txt"));
	//printf("%s", file_name);
	FILE* group_contacts = fopen(file_name, "r");
	//fseek(group_contacts, 0, SEEK_SET);
	//fgets(single_username, 100, group_contacts);
	//printf("%s\n", single_username);
	while (fgets(single_username, 100, group_contacts))
	{
		//printf("hello world!\n");
		int last = strlen(single_username);
		single_username[last - 1] = '\0';
		if (strcmp(single_username, username) == 0) return 1;
	}
	//fclose(group_contacts);
	return 0;
}

int is_in_channels(char channel_name[])
{
	char single_channel[50];
	FILE* channels = fopen("channels.txt", "r+");
	fseek(channels, 0, SEEK_SET);

	while (fgets(single_channel, 100, channels))
	{
		//printf("hello world!\n");
		int last = strlen(single_channel);
		single_channel[last - 1] = '\0';
		if (strcmp(single_channel, channel_name) == 0) return 1;
	}
	return 0;
	
}
int is_in_groups(char group_name[])
{
	char single_group[50];
	FILE* groups = fopen("groups.txt", "r");
	fseek(groups, 0, SEEK_SET);
	
		while (fgets(single_group, 100, groups))
		{
			//printf("hello world!\n");
			int last = strlen(single_group);
			single_group[last - 1] = '\0';
			if (strcmp(single_group, group_name) == 0) return 1;
		}
		return 0;
}

int is_in_contact_list(char reciever_name[], char username[])
{
	//printf("milad");
	//printf("%s\n", username);
	//printf("%s\n", reciever_name);

	char username_copy[100];
	char single_contact[100];
	strcpy(username_copy, username);
	//printf("%s", strcat(username_copy, "_contacts.txt"));
	FILE* user_contacts = fopen(strcat(username_copy, "_contacts.txt"), "r+");
	//fseek(user_contacts, 0, SEEK_SET);
	while (fgets(single_contact, 100, user_contacts))
	{
		//printf("hello world!\n");
		int last = strlen(single_contact);
		single_contact[last - 1] = '\0';	
		if (strcmp(single_contact, reciever_name) == 0) return 1;
	}
//	printf("hello world!\n");
	return 0;
}


int show_group_messages_to_user(SOCKET newconnection, char username[], char show_name[])
{
	char username_copy[50];
	char to_give_to_fuction[50];
	strcpy(to_give_to_fuction, show_name);
	char client_asw[50];
	strcpy(username_copy, username);
	char show_name_copy[50];
	strcpy(show_name_copy, show_name);
	strcat(show_name_copy, ".txt");
	char message[400];
	if (is_in_group_contact(username, show_name))
	{
		FILE* group_messages = fopen(show_name_copy, "r+");
		fgets(message, 400, group_messages);
		while (fgets(message, 400, group_messages))
		{
			send(newconnection, message, sizeof(message), 0);
			recv(newconnection, client_asw, sizeof(client_asw), 0);
		}
		send(newconnection, "End", sizeof("End"), 0);
		recv(newconnection, client_asw, sizeof(client_asw), 0);
		//	printf("%s\n", client_asw);
		send(newconnection, "finished", sizeof("finished"), 0);

		return 1;
	}
	send(newconnection, "you are not group user", sizeof("you are not group user"), 0);
	return 0;
}



int show_contact_messages_to_user(SOCKET newconnection,char username[], char show_name[])
{
//	printf("hello\n");
	char username_copy[50];
	char client_asw[50];
	strcpy(username_copy, username);
	char show_name_copy[50];
	strcpy(show_name_copy, show_name);
	strcat(username_copy, "_vs_");
	strcat(username_copy, show_name_copy);
	if (is_in_contact_list(show_name, username))
	{
		char message[400];
		FILE* messages = fopen(strcat(username_copy,".txt"), "r+");
		fseek(messages, 0, SEEK_SET);
		while (fgets(message, 400, messages))
		{
			send(newconnection, message, sizeof(message), 0);
			recv(newconnection, client_asw, sizeof(client_asw), 0);
		}
		send(newconnection, "End", sizeof("End"), 0);
		recv(newconnection, client_asw, sizeof(client_asw), 0);

		return 1;
	}
	
	return 0;
}

int send_message_to_contact(char message[], char username[], char reciever_name[])
{
	char username_copy[50];
	strcpy(username_copy, username);
	char reciever_copy[50];
	strcpy(reciever_copy, reciever_name);
//	printf("%s\n", username);
//	printf("%s\n", reciever_name);
//	printf("%s: %s", username_copy, reciever_copy);
	
//	printf("%s", strcat(username_copy, strcat("vs", reciever_copy),".txt"));
	if (is_in_contact_list(reciever_name, username))
	{

		//printf("hello");
		strcat(username_copy, "_vs_");
		strcat(username_copy, reciever_copy);
		strcat(username_copy, ".txt");
		//printf("%s\n", username_copy);
		FILE* pv_conversation1 = fopen(username_copy, "a+");
		fseek(pv_conversation1, 0, SEEK_END);
		fprintf(pv_conversation1, "%s : %s\n", username, message);
		fclose(pv_conversation1);
		printf("hello");
		reciever_copy[0] = '\0';
		strcpy(reciever_copy, reciever_name);
		strcat(reciever_copy, "_vs_");
		strcat(reciever_copy, username);
		strcat(reciever_copy, ".txt");
		//printf("%s\n", username_copy);
		FILE* pv_conversation2 = fopen(reciever_copy, "a+");
		fseek(pv_conversation2, 0, SEEK_END);
		fprintf(pv_conversation2, "%s : %s\n", username, message);
		fclose(pv_conversation2);
		return 1;
	}
	return 0;
}

int send_message_to_group(char message[], char username[], char reciever_name[])
{
	//printf("helloa");
	char group_name[50];
	strcpy(group_name, reciever_name);
	char group_name_copy[50];
	strcpy(group_name_copy, group_name);
	char username_copy[50];
	//printf("%s\n", reciever_name);
	if (is_in_group_contact(username , reciever_name))
	{
		//printf("hello");
		strcpy(username_copy, username);
		 FILE* group_file = fopen(strcat(group_name_copy, ".txt"), "a+");
		fprintf(group_file, "%s : %s\n", username, message);
		fclose(group_file);
		return 1;
	}
	//printf("hello");
	return 0;
}

int send_message_to_channel(char message[], char username[], char reciever_name[])
{
	char channel_name[50];
	strcpy(channel_name, reciever_name);
	char channel_name_copy[50];
	strcpy(channel_name_copy, channel_name);
	char username_copy[50];
	if (is_in_channel_contact(username, channel_name) && is_admin_of_channel(username, channel_name))
	{
		strcpy(username_copy, username);
		FILE* channel_file = fopen(strcat(channel_name_copy, "_chan.txt"), "a+");
		fprintf(channel_file, "admin : %s\n", message);
		fclose(channel_file);
		return 1;
	}
}


void start_program(SOCKET newconnection, char username[]) // when user 
{
	char new_contact_name[50];
	//printf("hello world!");
	//send(newconnection, "startprogram", sizeof("startprogram"), 0);
	send(newconnection, "hello", sizeof("hello"), 0);
	
	recv(newconnection, whattodo, sizeof(whattodo), 0);
	printf("%s\n", whattodo);
	if (strcmp(whattodo, "Add contact") == 0 || strcmp(whattodo, "add contact") == 0)// the user want's to add the contact
	{
		char copy_of_username[50];
		strcpy(copy_of_username, username);
		send(newconnection, "send contact name", sizeof("send contact name"), 0);
		recv(newconnection, new_contact_name, sizeof(new_contact_name), 0);
		//	printf("%s", new_contact_name);
		if (!is_in_users(new_contact_name))
		{
			FILE* user_contacts = fopen(strcat(copy_of_username, "_contacts.txt"), "a+");
			fprintf(user_contacts, "%s\n", new_contact_name);
			fclose(user_contacts);
			send(newconnection, "saved", sizeof("saved"), 0);
			start_program(newconnection, username);
		}
		else
		{
			send(newconnection, "not", sizeof("not"), 0);
			start_program(newconnection, username);
		}
	}
	else if (strcmp(whattodo, "show contacts") == 0)
	{
		char client_buf[40];
		send(newconnection, "you wants contacts", sizeof("you wants contacts"), 0);
		recv(newconnection, client_buf, sizeof(client_buf), 0);
		char all_contacts[1000] = {};
		char simple_contact[50];
		char copy_of_username[50];
		strcpy(copy_of_username, username);
		FILE* user_contacts = fopen(strcat(copy_of_username, "_contacts.txt"), "r+");
		while (fgets(simple_contact, 100, user_contacts))
		{
			int last = strlen(simple_contact);
			simple_contact[last - 1] = '-';
			strcat(all_contacts, simple_contact);		
		}
		send(newconnection, all_contacts, sizeof(all_contacts), 0);
		fclose(user_contacts);
		start_program(newconnection,username);
	}

	else if (strcmp(whattodo, "create group") == 0) // to create a new group
	{
		char group_name[50];
		send(newconnection, "send new group name", sizeof("send new group name"), 0);
		recv(newconnection, group_name, sizeof(group_name), 0);
		//printf("%s\n", group_name);
		if (!is_in_groups(group_name))
		{
			char copy_of_group_name[50];
			char copy_of_group_name1[50];
			strcpy(copy_of_group_name1, group_name);
			strcpy(copy_of_group_name, group_name);
			FILE* group = fopen(strcat(copy_of_group_name, ".txt"), "a+");
			fseek(group, 0, SEEK_END);
			fprintf(group, "admin:%s\n", username);
			fclose(group);
			FILE* groups = fopen("groups.txt", "a+");
			fseek(groups, 0, SEEK_END);
			fprintf(groups, "%s\n", group_name);
			fclose(groups);
			FILE* group_contact = fopen(strcat(copy_of_group_name1, "_contacts.txt"), "a+");
			fprintf(group_contact, "%s\n", username);				
			fclose(group_contact);
			send(newconnection, "created", sizeof("group have beed created"), 0);
			
			start_program(newconnection, username);
			
		}
		else
		{
			send(newconnection, "This group name existed", sizeof("this group name existed"), 0);
			start_program(newconnection, username);
		}

	}
	else if (strcmp(whattodo, "join group") == 0) // to add a new existed group to contacts
	{

	//	printf("%c", groups[0][0]);
	//	printf("ehlload");
		char group_name[50];
		send(newconnection, "send group name", sizeof("send group name"), 0);
		recv(newconnection, group_name, sizeof(group_name), 0);
		//printf("%s\n", group_name);
		if (is_in_groups(group_name) && !is_in_group_contact(username , group_name))
		{
			printf("%s\n", group_name);
			char copy_of_username[50];
			strcpy(copy_of_username, username);
			char copy_of_group_name[50];
			strcpy(copy_of_group_name, group_name);
			FILE* group_file = fopen(strcat(copy_of_group_name, "_contacts.txt"), "a+");
			//fseek(group_file, 0, SEEK_END);
			fprintf(group_file, "%s\n", username);
			fclose(group_file);
			FILE* user_group = fopen(strcat(copy_of_username, "_groups.txt"), "a+");
		//	fseek(user_group, 0, SEEK_END);
			fprintf(user_group, "%s\n", group_name);
			fclose(user_group);
			send(newconnection, "you're added", sizeof("you're added"), 0);
			start_program(newconnection, username);
		}
		else
		{
			send(newconnection, "not", sizeof("not"), 0);
			start_program(newconnection, username);
		}
	
	}
	else if (strcmp(whattodo, "create channel") == 0) // user wants to creat a new channel.
	{
		char channel_name[50];
		send(newconnection, "send new channel name", sizeof("send new channel name"), 0);
		recv(newconnection, channel_name, sizeof(channel_name), 0);
	//	printf("helloworld\m");
		if (!is_in_channels(channel_name))
		{
		//	printf("hello\n");
			char copy_channel_name[50];
			strcpy(copy_channel_name, channel_name);
			FILE* channel = fopen(strcat(copy_channel_name, "_chan.txt"), "a+"); // remember this important thinggggg..**YU&(*&(
			fseek(channel, 0, SEEK_END);
			fprintf(channel, "admin:%s\n", username);
			fclose(channel);
			FILE* channels = fopen("channels.txt", "a+");
			fseek(channels, 0, SEEK_END);
			fprintf(channels, "%s\n", channel_name);
			fclose(channels);
			char copy_channel_name2[50];
			strcpy(copy_channel_name2, channel_name);
			FILE* channel_users = fopen(strcat(copy_channel_name2, "_chan_contacts.txt"), "a+");
			fprintf(channel_users, "%s\n", username);
			fclose(channel_users);
			send(newconnection, "created", sizeof("channel have beed created"), 0);

			start_program(newconnection, username);

		}
		else
		{
			send(newconnection, "This channel name existed", sizeof("this channel name existed"), 0);
			start_program(newconnection, username);
		}
	}
	else if (strcmp(whattodo, "join channel") == 0) // to add a new existed channel to contacts
	{
		char channel_name[50];
		send(newconnection, "send channel name", sizeof("send channel name"), 0);
		recv(newconnection, channel_name, sizeof(channel_name), 0);
		
		if (is_in_channels(channel_name) && !is_in_channel_contact(username, channel_name))
		{
			
			char copy_of_username[50];
			strcpy(copy_of_username, username);
			char copy_of_channel_name[50];
			strcpy(copy_of_channel_name, channel_name);
			FILE* channel_file = fopen(strcat(copy_of_channel_name, "_chan_contacts.txt"), "a+");
			fseek(channel_file, 0, SEEK_END);
			fprintf(channel_file, "%s\n", username);
			fclose(channel_file);
			FILE* user_channel = fopen(strcat(copy_of_username, "_channels.txt"), "a+");
			fseek(user_channel, 0, SEEK_END);
			fprintf(user_channel, "%s\n", channel_name);
			fclose(user_channel);
			send(newconnection, "you're added", sizeof("you're added"), 0);
			start_program(newconnection, username);
		}
		else
		{
			send(newconnection, "not", sizeof("not"), 0);
			start_program(newconnection, username);
		}

	}



	else if (strcmp(whattodo, "send message") == 0)
	{
		char message[300];
		char reciever_name[50];
		char reciever_type[50];
		send(newconnection, "send reciever", sizeof("send reciever"), 0);
		recv(newconnection, reciever_name, sizeof(reciever_name), 0);
		send(newconnection, "send reciever type", sizeof("send reciever type"), 0);
		recv(newconnection, reciever_type, sizeof(reciever_type), 0);
		if (strcmp(reciever_type, "contact") == 0)
		{
			//printf("heloo\n");
			send(newconnection, "send your message", sizeof("send your message"), 0);
			recv(newconnection, message, sizeof(message), 0);
		//	printf("%s", message);
			int result = send_message_to_contact(message, username, reciever_name);
			if (result == 1)
			{
				send(newconnection, "you're message have been sent", sizeof("you're message have been sent"), 0);
				start_program(newconnection, username);
			}
			else
			{
				send(newconnection, "you have Entered an invalid contact", sizeof("you have Entered an invalid contact"), 0);
				start_program(newconnection, username);
			}
		}
		else if (strcmp(reciever_type, "group") == 0)
		{
		//	printf("hello");
			send(newconnection, "send you message" , sizeof("send you message") , 0);
			recv(newconnection, message, sizeof(message), 0);
			int result = send_message_to_group(message, username, reciever_name);
			if (result == 1)
			{
				send(newconnection, "you're message have been sent", sizeof("you're message have been sent"), 0);
				start_program(newconnection, username);
			}

			else 
			{
				send(newconnection, "Sorry,You are not a user of this group", sizeof("Sorry,You are not a user of this group"), 0);
				start_program(newconnection, username);
			}
		}
		else if (strcmp(reciever_type, "channel") == 0)
		{
			//	printf("hello");
			send(newconnection, "send you message", sizeof("send you message"), 0);
			recv(newconnection, message, sizeof(message), 0);
			int result = send_message_to_channel(message, username, reciever_name);
			if (result == 1)
			{
				send(newconnection, "you're message have been sent", sizeof("you're message have been sent"), 0);
				start_program(newconnection, username);
			}

			else
			{
				send(newconnection, "Sorry,You are not admin of this channel", sizeof("Sorry,You are not a user of this group"), 0);
				start_program(newconnection, username);
			}
		}
		else
		{
			send(newconnection, "you're input of type of contact is incorrect", sizeof("you're input of type of contact is incorrect"), 0);
			start_program(newconnection, username);
		}
		
	}
	else if (strcmp(whattodo, "show messages") == 0) // to add a new existed group to contacts
	{
		char show_type[50];
		char show_name[50];
		char user_mas[50];
		send(newconnection, "you want messages", sizeof("you want messages"), 0);
		recv(newconnection, show_type, sizeof(show_type), 0);
		send(newconnection, "send show_name", sizeof("send show_name"), 0);
		recv(newconnection, show_name, sizeof(show_name), 0);
		if (strcmp(show_type, "contact") == 0)
		{
			int result = show_contact_messages_to_user(newconnection,username, show_name);
			if (result == 1)
			{
				send(newconnection, "finished", sizeof("finished"), 0);
				start_program(newconnection, username);

			}
			else
			{
				send(newconnection, "There is no conversation between you", sizeof("There is no conversation between you"), 0);
				start_program(newconnection, username);
			}
			
		}
		else if (strcmp(show_type, "group") == 0)
		{
			int result = show_group_messages_to_user(newconnection, username, show_name);
			start_program(newconnection, username);
		}
	}

	else if (strcmp(whattodo, "log out") == 0)
	{
		char client_buff[40];
		send(newconnection, "log out", sizeof("log out"), 0);
		recv(newconnection, client_buff, sizeof(client_buff), 0);
		exit(0);
	}

	else {
		send(newconnection, "invalid", sizeof("invalid"), 0);
		start_program(newconnection, username);
	}
}






void find(char string[], char username[], char password[])
{
	int limit = strlen(string);
	char make_character[5] = "hell";
	char c;
	char user[50] = {};
	int user_couter = 0;
	char pass[50] = {};
	int pass_couter = 0;
	int where_is = 1;
	for (int i = 0 ; i<limit; i++)
	{
		c = string[i];
		//make_character[0] = c;
		//make_character[1] = '\0';
		if (c == ' ')
			continue;
		if (c == ':')
		{
			where_is = i;
			user[user_couter] = '\0';
			user_couter++;
			strcpy(username, user);
		}
		else if (c == '\n')
		{
			pass[pass_couter] = '\0';
			pass_couter++;
			strcpy(password, pass);
		}
		else if (i < where_is)
		{
			user[user_couter] = c;
			user_couter++;
		//	strcat(user, make_character);
			where_is++;
		}
		else if (i > where_is)
		{
			pass[pass_couter] = c;
			pass_couter++;
			//strcat(pass, make_character);
		}

	}
}

void find_the_username_in_userpass(char  username[], char cor_password[])
{
	FILE* user_pass = fopen("userpass.txt", "r+");
	char user_and_pass[100];
	while (fgets(user_and_pass, 100, user_pass))
	{

		char username_i[50];
		char password[50];
		find(user_and_pass, username_i, password);
		printf("%s\n", username_i);
		//printf("%s : %s\n", username_i, password);
		if (strcmp(username, username_i) == 0)
		{
			strcpy(cor_password, password);
			return;
		}
	}
	fclose(user_pass);
	strcpy(cor_password, "yo");
	return;
}

void save_user_pass(char username[], char password[])
{
	FILE* user_pass = fopen("userpass.txt", "a+");
	fprintf(user_pass, "%s : %s", username, password);
	fclose(user_pass);
}

void sign_in(SOCKET newconnection)
{
	//printf("hello");
	char username[50];
	char cor_password[30];
	char password[30];
	char client_buf[40];
	//int success = send(newconnection, "Send Username", sizeof("send Username"), 0);

	recv(newconnection, username, sizeof(username), 0);
	find_the_username_in_userpass(username, cor_password);
	//send(newconnection, "send password", sizeof("send password"), 0);
	recv(newconnection, password, sizeof(password), 0);
	//printf("%s\n%s\n", cor_password, password);
	//	printf("%s : %s ", username, password);
	//	printf("%d\n", strcmp(cor_password, password));
	int index = strlen(cor_password);
	printf("%s\n", password);
	printf("%s\n", cor_password);
	//cor_password[index - 1] = '\0';
	if (strcmp(cor_password, password) == 0)
	{
		send(newconnection, "correct", sizeof("correct"), 0);
		start_program(newconnection , username);
	}
	else
	{
		send(newconnection, "incorrect", sizeof("incorrect"), 0);
	//	sign_in(newconnection);
	}
	
}



void sign_up(SOCKET newconnection)
{
	char username[50];
	char password[30];
	int success = send(newconnection, "Send Username", sizeof("send Username"), 0);
	if (success != -1)
	success = recv(newconnection, username, sizeof(username), 0);
	//send(newconnection, "Was send", sizeof("Was send"), 0);
	if (success != -1)
	recv(newconnection, password, sizeof(password), 0);
//	printf("%s   %s\n", username, password);
	save_user_pass(username,password);
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

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, 0);//create socket to listen for few connections
	bind(slisten, (SOCKADDR*)&address, sizeof(address));// bind the address to the socket
	listen(slisten, SOMAXCONN);// places slisten socket in a state in which it is listening for an 

	SOCKET newconnection;// sochet to hold the client's connection
	newconnection = accept(slisten, (SOCKADDR*)&address, &addrlen);// accept a new connection


	if (newconnection == 0) // if accepting the client connection failed
	{
		perror("failed to accept the client's connetctions");
	}


	else
	{
		puts("client is connected!");
	}
	while (1)
	{


		recv(newconnection, whattodo, sizeof(whattodo), 0);
	//	printf("%s\n", whattodo);

		if (strcmp(whattodo, "sign up") == 0) sign_up(newconnection);

		else if (strcmp(whattodo, "sign in") == 0) sign_in(newconnection);

		else
		{
			main();
		}
	}















	return 0;
}