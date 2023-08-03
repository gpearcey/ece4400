#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#define CAPACITY 50000 // Size of the HashTable.

using namespace std;

class HashTable
{
private:
    struct Item
    {
        char* key;
        char* value;
    };

    // Defines the HashTable.
    struct Table
    {
        // Contains an array of pointers to items.
        Item** items;
        std::vector<std::list<Item*>> overflow_buckets;
        int size;
        int count;
    };

    unsigned long hash_function(char* str)
    {
        unsigned long i = 0;

        for (int j = 0; str[j]; j++) //continues until it reaches the null-terminator character '\0'
            i += str[j];

        return i % CAPACITY;
    }

    void handle_collision(unsigned long index, Item& item)
    {
        std::cout << "test" << std::endl;
        std::list<Item*> head = this->table->overflow_buckets[index];
        std::cout << "test 2" << std::endl;
        if (head.empty())
        {
            // Creates the list.
            head.push_back(&item);
            table->overflow_buckets[index] = head;
        }
        else {
            // Insert to the list.
            table->overflow_buckets[index].push_back(&item);
        }
        return;
    }

    void free_item(Item* item)
    {
        // Frees an item.
        free(item->key);
        free(item->value);
        free(item);
    }

public:

    HashTable()
    {
        // Creates a new HashTable.
        table = (Table*) malloc(sizeof(Table));
        table->size = CAPACITY;
        table->count = 0;
        table->items = (Item**) calloc(table->size, sizeof(Item*));

        for (int i = 0; i < table->size; i++)
            table->items[i] = NULL;
    }

    void addItem(char* key, char* value)
    {
        // Creates a pointer to a new HashTable item.
        Item* item = (Item*) malloc(sizeof(Item));
        item->key = (char*) malloc(strlen(key) + 1);
        item->value = (char*) malloc(strlen(value) + 1);
        strcpy(item->key, key);
        strcpy(item->value, value);

        int index = hash_function(key);

        Item* current_item = this->table->items[index];

        if (current_item == NULL)
        {
            // Key does not exist.
            if (table->count == table->size)
            {
                // HashTable is full.
                printf("Insert Error: Hash Table is full\n");
                free_item(item);
                return;
            }

            // Insert directly.
            table->items[index] = item;
            table->count++;
        }
        else if (strcmp(current_item->key, key) == 0) // Key already exsists at this index
        {
            // Update the value
            strcpy(table->items[index]->value, value);
        }
        else // Collision
        {
            handle_collision(index, *item);
        }
        return;
    }

    void print_table()
    {
        printf("\nHash Table\n-------------------\n");
    
        for (int i = 0; i < this->table->size; i++)
        {
            if (this->table->items[i])
            {
                printf("Index:%d, Key:%s, Value:%s\n", i, this->table->items[i] -> key, this->table->items[i]->value);
            }
        }
    
        printf("-------------------\n\n");
    }

private:


    Table* table;
};
