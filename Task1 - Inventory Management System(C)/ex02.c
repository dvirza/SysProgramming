/*
 *      Dvir Zaguri     315602284
 *      Ben Haimoff     206563660
        This program was written by us and only by us.
        Every attempt to copy the code or part of it, will consider as theft and will handle accordingly
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* structures */
typedef struct item {
    char* name;
    int  id;
    struct wlst* warehouses;
} item;

typedef struct warehouse {
    char* location;
    int  code;
    struct itemlst* items;
} warehouse;

typedef struct itemlst {
    item* data;
    struct itemlst* next;
} itemlst;

typedef struct wlst {
    warehouse* data;
    struct wlst* next;
} wlst;

/*DO NOT TOUCH THIS FUNCTION */
void getstring(char* buf, int length) {
    int len;
    //buf = fgets(buf, length, stdin);
	scanf("%s", buf);
    len = (int)strlen(buf);
    if (buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}

/*DO NOT TOUCH THIS FUNCTION */
void print_error_message(int errid) {
	#ifdef DEBUGON
	fprintf(stderr, "BGU ERROR %d\n", errid);
	#else
	fprintf(stderr, "BGU ERROR\n");	
	#endif
	exit(-1);
}

//  Create a New item
item* newItem(const char* name, int id) {
    item* new_item = (item*)malloc(sizeof(item));
    new_item->name = strdup(name); // Allocate memory and copy name
    new_item->id = id;
    new_item->warehouses = NULL;
    return new_item;
}
//  Check if item ID or warehouse code input is valid
void checkID(int id, int is_int){
    if (id >= INT16_MAX | id < 0 )
    {
        print_error_message(id);
    }
    if (!is_int) {
        print_error_message(id);
    }
}

// Create a New Warehouse
warehouse* newWarehouse(const char* location, int code) {
    warehouse* new_warehouse = (warehouse*)malloc(sizeof(warehouse));
    new_warehouse->location = strdup(location); // Allocate memory and copy name
    new_warehouse->code = code;
    new_warehouse->items = NULL;
    return new_warehouse;
}

//  LINKED LIST : Create a new item node
itemlst* new_item_node(item* data) {
    itemlst* new_node = (itemlst*)malloc(sizeof(itemlst));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

//   LINKED LIST : Create a new warehouse node 
wlst* new_warehouse_node(warehouse* data) {
    wlst* new_node = (wlst*)malloc(sizeof(wlst));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Free memory allocated for item l-list 
void free_item_list(itemlst* head) {
    itemlst* current = head;
    while (current != NULL) {
        itemlst* temp = current;
        current = current->next;
        free(temp->data->name);
        free(temp->data);
        free(temp);
    }
}

// Free memory allocated for warehouse l-list
void free_warehouse_list(wlst* head) {
    wlst* current = head;
    while (current != NULL) {
        wlst* temp = current;
        current = current->next;
        free(temp->data->location);
        free(temp->data);
        free(temp);
    }
}

// Compare items by ID
int compare_items(const void* a, const void* b) {
    item* itemA = *(item**)a;
    item* itemB = *(item**)b;
    return (itemA->id - itemB->id);
}

// Count items in the list
int count_items(itemlst* head) {
    int count = 0;
    itemlst* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Convert the linked list to an array of pointers
item** list_to_array(itemlst* head, int count) {
    item** array = (item**)malloc(count * sizeof(item*));
    itemlst* current = head;
    for (int i = 0; i < count; i++) {
        array[i] = current->data;
        current = current->next;
    }
    return array;
}


// Modified print_items function to print the sorted list
void print_items(itemlst* head) {
    int count = count_items(head);
    if (count == 0) {
        printf("No items to print.\n");
        return;
    }
    item** array = list_to_array(head, count);
    qsort(array, count, sizeof(item*), compare_items);
    for (int i = 0; i < count; i++) {
        printf("%d:%s\n", array[i]->id, array[i]->name);
        
        // Print the warehouses assigned to the item
        if (array[i]->warehouses != NULL) {
            printf("Item Warehouses:");
            wlst* current_warehouse = array[i]->warehouses;
            while (current_warehouse != NULL) {
                printf("%d-%s, ", current_warehouse->data->code, current_warehouse->data->location);
                current_warehouse = current_warehouse->next;
            }
            printf("\n");
        }
    }
    // Free the allocated array
    free(array);
}


// Get the count of nodes in the warehouse list
int count_warehouses(wlst* head) {
    int count = 0;
    wlst* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
// Comparison function for qsort
int compare_warehouses(const void* a, const void* b) {
    warehouse* warehouseA = *(warehouse**)a;
    warehouse* warehouseB = *(warehouse**)b;
    return (warehouseA->code - warehouseB->code);
}
//  Print warehouses list in order of their code
void print_warehouses(wlst* head) {
    int count = count_warehouses(head);
    if (count == 0) {
        printf("Warehouse List is empty.\n");
        return;
    }
    // Create an array of warehouse pointers
    warehouse** warehouse_array = (warehouse**)malloc(count * sizeof(warehouse*));
    if (warehouse_array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    // Collect the warehouses into the array
    wlst* current = head;
    for (int i = 0; i < count; i++) {
        warehouse_array[i] = current->data;
        current = current->next;
    }
    // Sort the array by warehouse code
    qsort(warehouse_array, count, sizeof(warehouse*), compare_warehouses);
    // Print the sorted warehouses
    for (int i = 0; i < count; i++) {
        printf("Warehouse code %d, Warehouse name: %s\n", warehouse_array[i]->code, warehouse_array[i]->location);

        // Collect items in a temporary list
        itemlst* item_current = warehouse_array[i]->items;
        itemlst* reversed_items = NULL;
        while (item_current != NULL) {
            printf("items:");

            itemlst* temp = new_item_node(item_current->data);
            temp->next = reversed_items;
            reversed_items = temp;
            item_current = item_current->next;
        }
        // Print items in reverse order
        itemlst* temp_current = reversed_items;
        while (temp_current != NULL) {
            printf(" ID %d Name %s |", temp_current->data->id, temp_current->data->name);
            temp_current = temp_current->next;
        }
        // Free the temporary list
        while (reversed_items != NULL) {
            itemlst* temp = reversed_items;
            reversed_items = reversed_items->next;
            free(temp);
        }
    }
    free(warehouse_array);
}

// Function to find an item by ID
item* find_item_by_id(itemlst* items, int id) {
    itemlst* current = items;
    while (current != NULL) {
        if (current->data->id == id) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

// Function to find a warehouse by code
warehouse* find_warehouse_by_code(wlst* warehouses, int code) {
    wlst* current = warehouses;
    while (current != NULL) {
        if (current->data->code == code) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void assign_item_to_warehouse(itemlst* items, wlst* warehouses, int item_id, int warehouse_code) {
    item* item_to_assign = find_item_by_id(items, item_id);
    warehouse* warehouse_to_assign = find_warehouse_by_code(warehouses, warehouse_code);

    if (item_to_assign == NULL) {
        print_error_message(item_id);
        return;
    }
    if (warehouse_to_assign == NULL) {
        print_error_message(warehouse_code);
        return;
    }
    // Create new nodes for the linked lists
    wlst* new_warehouse_node = (wlst*)malloc(sizeof(wlst));
    new_warehouse_node->data = warehouse_to_assign;
    new_warehouse_node->next = item_to_assign->warehouses;
    item_to_assign->warehouses = new_warehouse_node;
    itemlst* new_item_node = (itemlst*)malloc(sizeof(itemlst));
    new_item_node->data = item_to_assign;
    new_item_node->next = warehouse_to_assign->items;
    warehouse_to_assign->items = new_item_node;
}

void unassign_item_to_warehouse(itemlst* items,wlst* warehouses,int item_id,int warehouse_code) {
    item* item_to_unassign = find_item_by_id(items, item_id);
    warehouse* warehouse_to_unassign = find_warehouse_by_code(warehouses, warehouse_code);
        //wrong id or code handler:
    if (item_to_unassign == NULL) {
        print_error_message(item_id);
        return;
    }
    if (warehouse_to_unassign == NULL) {
        print_error_message(warehouse_code);
        return;
    }
    // Remove item from warehouse's items list
    itemlst* prev_item_node = NULL;
    itemlst* current_item_node = warehouse_to_unassign->items;
    while (current_item_node != NULL && current_item_node->data != item_to_unassign) { // finding the items to unssign nodes in the list of the itemlst
        prev_item_node = current_item_node;
        current_item_node = current_item_node->next;
    } // item to unassign node found
    if (current_item_node == NULL) { // unssign item from a warehouse its not assigned to error
        print_error_message(item_id);
    } else {
        if (prev_item_node == NULL) {
            // Removing the first item node
            warehouse_to_unassign->items = current_item_node->next;
        } else {
            // Removing a node other than the first one
            prev_item_node->next = current_item_node->next;
        }
        free(current_item_node);
    }
    // Remove warehouse from item's warehouses list
    wlst* prev_warehouse_node = NULL;
    wlst* current_warehouse_node = item_to_unassign->warehouses;
    while (current_warehouse_node != NULL && current_warehouse_node->data != warehouse_to_unassign) {
        prev_warehouse_node = current_warehouse_node;
        current_warehouse_node = current_warehouse_node->next;
    }
    if (current_warehouse_node == NULL) {
        print_error_message(warehouse_code);
    } else {
        if (prev_warehouse_node == NULL) {
            // Removing the first warehouse node
            item_to_unassign->warehouses = current_warehouse_node->next;
        } else {
            // Removing a node other than the first one
            prev_warehouse_node->next = current_warehouse_node->next;
        }
        free(current_warehouse_node);
    }
}
// Insert a new item into the items list
itemlst* insert_item(itemlst* head, item* new_item) {
    itemlst* new_node = new_item_node(new_item);
    if (head == NULL) {
        return new_node;
    } else {
        itemlst* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return head;
    }
}

// Insert a new warehouse into the warehouses list
wlst* insert_warehouse(wlst* head, warehouse* new_warehouse) {
    wlst* new_node = new_warehouse_node(new_warehouse);
    if (head == NULL) {
        return new_node;
    } else {
        wlst* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return head;
    }
}

/*DO NOT TOUCH THIS MAIN TEMPLATE - ONLY ADD YOUR FUNCTIONS CALLS */
int main() {

    itemlst* items = 0;
    wlst* warehouses = 0;
    item* new_item = NULL; //
    warehouse* new_warehouse = NULL; //
    
    char  c;
    char  buf[100];
    int   id, num;
    int   is_int;


    do {
        printf("Choose:\n"
            "    i - new item\n"
            "    w - new warehouse\n"
            "    a - assign an item to a warehouse\n"
            "    u - unassign an item from a warehouse(not delete!)\n"
            "    p - print status\n"
			"    g - generating and assigning 100 items to 10 warehouses\n"
            "    q - quit\n");

        while ((c = (char)getchar()) == '\n');
        getchar();

        switch (c) {
        case 'i':
            printf("Adding new item.\n");
            printf("item name: ");
            getstring(buf, 100);
            printf("item ID: ");
            is_int = scanf("%d", &id);
            checkID(id, is_int);
            if (strlen(buf) > 100)
            {
                printf("malloc(): corrupted top size\nAborted");
                exit(-1);
            }
            
            if (find_item_by_id(items, id) == NULL){
                printf("\n Add new item: name %s item id: %d",buf, id);
                new_item = newItem(buf, id);
                if (items == NULL) {
                    items = new_item_node(new_item);
                } else {
                    itemlst* current = items;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = new_item_node(new_item);
                }
            }
            break;

        case 'w':
            printf("Adding new warehouse.\n");
            printf("\n warehouse name: ");
            getstring(buf, 100);
            printf("\n warehouse code: ");
            is_int = scanf("%d", &num);
            checkID(num, is_int);
            
            if (strlen(buf) > 100)
            {
                printf("malloc(): corrupted top size\nAborted");
                exit(-1);
            }

            if (find_warehouse_by_code(warehouses,num) == NULL){
                new_warehouse = newWarehouse(buf, num);
                if (warehouses == NULL) {
                    warehouses = new_warehouse_node(new_warehouse);
                } else {
                    wlst* current = warehouses;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = new_warehouse_node(new_warehouse);
                }
                printf("\n Add new warehouse: name %s warehouse code: %d",buf, num);
            }
            
            break;

        case 'a':
            printf("Assign an item to a warehouse.\n");
            printf("item ID: ");
            scanf("%d", &id);
            printf("warehouse code: ");
            scanf("%d", &num);
            assign_item_to_warehouse(items, warehouses, id, num);
            break;

        case 'u':
            printf("Remove an item from a warehouse.\n");
            printf("item ID: ");
            scanf("%d", &id);
            printf("warehouse code: ");
            scanf("%d", &num);
            unassign_item_to_warehouse(items, warehouses, id, num);
            break;

        case 'p':
            printf("Printing status.\nitem LIST:\n");
            print_items(items);
            printf("warehouse LIST:\n");
            print_warehouses(warehouses);
            break;
			
		case 'g':  // generating and assigning items and warehouses
			printf("Generating and assigning items to warehouses\n");
            srand(1948);
            //Generate items
			for(int i = 0; i < 100; i++){
                id = i;
                if (find_item_by_id(items, id) == NULL){
                    char name[20];
                    sprintf(name, "Item%d", id);
                    items = insert_item(items, newItem(name, id));
                }
            }
            //Generate warehouses
            for(int i = 0; i < 10; i++ ){
                num = i;
                // Check if warehouse with the same code already exists
                if (find_warehouse_by_code(warehouses,num) == NULL){
                    char location[20];
                    sprintf(location, "Warehouse%d", num);
                    warehouses = insert_warehouse(warehouses, newWarehouse(location,num));
                }
            }
            itemlst* current_item = items;
            while (current_item != NULL){
                int random_code = rand() % 10; // randomize warehouse
                assign_item_to_warehouse(items, warehouses, current_item->data->id, random_code);
                current_item = current_item->next;
            }
			break;

        case 'q':
            printf("Quitting...\n");
            break;
        }

        if (c != 'q')
            printf("\n");
    } while (c != 'q');

    free_item_list(items);
    free_warehouse_list(warehouses);
	exit(0);
}