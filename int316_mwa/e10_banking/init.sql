CREATE DATABASE banking_system;
GRANT ALL PRIVILEGES ON banking_system.* TO 'lab_user'@'localhost';

USE banking_system;

CREATE TABLE customers(
    customer_id VARCHAR(30) PRIMARY KEY,
    username VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    balance DECIMAL(10, 2) NOT NULL,
    pwd VARCHAR(50) NOT NULL
);

CREATE TABLE transactions(
    transaction_id INTEGER PRIMARY KEY,
    customer_id VARCHAR(30) NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    transaction_type CHAR(2) NOT NULL,
    transaction_date DATE NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers (customer_id)
);

INSERT INTO customers(customer_id, username, email, balance)
    VALUES("abc123", "test", "k@gmail.com", 132.23);
