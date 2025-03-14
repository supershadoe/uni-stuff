CREATE DATABASE ResMgr;
GRANT ALL PRIVILEGES ON ResMgr.* TO 'lab_user'@'localhost';
USE ResMgr;

CREATE TABLE Users(
    Username CHAR(4) NOT NULL,
    Pwd VARCHAR(50) NOT NULL
);

CREATE TABLE Employee(
    EmployeeId INT PRIMARY KEY AUTO_INCREMENT,
    EmployeeName VARCHAR(50) NOT NULL,
    Experience INT NOT NULL,
    CHECK (Experience > 0)
) AUTO_INCREMENT = 100;

CREATE TABLE Project(
    ProjectId INT PRIMARY KEY AUTO_INCREMENT,
    ProjectName VARCHAR(50) NOT NULL,
    ClientName VARCHAR(50) NOT NULL
);

CREATE TABLE ProjectAllocation(
    AllocationId INT PRIMARY KEY AUTO_INCREMENT,
    ProjectId INT NOT NULL,
    EmployeeId INT NOT NULL,
    StartDate DATE NOT NULL,
    EndDate DATE NOT NULL,
    FOREIGN KEY (ProjectId) REFERENCES Project (ProjectId),
    FOREIGN KEY (EmployeeId) REFERENCES Employee (EmployeeId)
);

INSERT INTO Users (Username, Pwd) VALUES ('user', 'hello123');
INSERT INTO Employee (EmployeeName, Experience)
    VALUES ('Akilan', 8), ('Yogesh', 2);
INSERT INTO Project (ProjectName, ClientName)
    VALUES
        ('Core Banking solution', 'Silicon Valley Bank'),
        ('Landing site', 'Bigbasket')
    ;
