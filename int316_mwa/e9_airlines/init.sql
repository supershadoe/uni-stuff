CREATE DATABASE airline_db;
GRANT ALL PRIVILEGES ON airline_db.* TO 'lab_user'@'localhost';

USE airline_db;

CREATE TABLE users(
    userid INT PRIMARY KEY AUTO_INCREMENT,
    fullname VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    password VARCHAR(100) NOT NULL
) AUTO_INCREMENT = 1000;

CREATE TABLE flights(
    flightid INT PRIMARY KEY AUTO_INCREMENT,
    source CHAR(3) NOT NULL,
    dest CHAR(3) NOT NULL,
    dep_time DATETIME NOT NULL,
    arr_time DATETIME NOT NULL
) AUTO_INCREMENT = 1000;

CREATE TABLE bookings(
    bookingid INT PRIMARY KEY AUTO_INCREMENT,
    flightid INT NOT NULL,
    userid INT NOT NULL,
    FOREIGN KEY (flightid) REFERENCES flights(flightid),
    FOREIGN KEY (userid) REFERENCES users(userid)
) AUTO_INCREMENT = 100;

INSERT INTO users(fullname, email, password) VALUES ('test', 'test@x.com', 'test@123');

INSERT INTO flights(source, dest, dep_time, arr_time) VALUES
    ('LAX', 'DEL', '1970-01-01 12:15:00', '1970-01-01 15:20:00'),
    ('NRT', 'LAX', '1970-01-01 08:35:00', '1970-01-01 09:50:00');
