Del's Cafe Inventory System

Del’s Café Inventory System is a console-based application written in the C programming language that helps café staff efficiently manage products, stock levels, and customer orders. When new items arrive, staff can register them by entering details such as product name, category, price, and quantity. The system allows users to update product information, remove items, and monitor stock availability to ensure that the café operates smoothly without shortages or overstocking.

In addition to inventory management, the system supports customer order processing. Staff can create orders by selecting items from the inventory, automatically updating stock quantities as purchases are made. Each transaction is recorded, allowing the system to maintain a history of all completed orders. This ensures accurate tracking of sales and inventory movement over time.

The main purpose of this project is to apply fundamental Data Structures and Algorithms (DSA) concepts learned in CC104 in a practical and functional system. It demonstrates how theoretical knowledge can be used to build an efficient inventory management solution while improving problem-solving, data handling, and program design skills.

📌Data Structures Used

1. Array
-Used to store the list of products in the inventory
Allows fast access using index

2. Linked List
-Used to store transaction history
Supports dynamic memory allocation

3. Stack
-Used for undo functionality
Follows LIFO (Last In, First Out)

4. Queue
-Used to manage customer orders
Follows FIFO (First In, First Out)

Algorithms Used
	1. Linear Search
	    -Used to find products by ID
            -Simple and effective for small datasets
	2. Bubble Sort
	    -Used to sort inventory items by quantity
	    -Demonstrates basic sorting logic
	3. Queue Processing (FIFO)
	    -Used to process customer orders in correct order

Features
	Add new products
	View all products
	Update product details
	Delete products
	Search for products
	Sort inventory by quantity
	View transaction history
	Undo last operation
	Add customer orders
	Process customer orders

How to Compile and Run
	Step 1: Install Compiler
	Install a C compiler such as:
		MinGW / TDM-GCC / WSL
	Step 2: Compile the Program
		Open terminal and run.
