-- Expt 5 SQL Commands using Joins (Inner and outer)

SELECT * FROM Printer, Product_Info;

SELECT * FROM PC, Product_Info, Laptop;

SELECT
  W.Worker_Name, Age, Skill
  FROM Worker W JOIN WorkerSkill WS
  ON W.Worker_Name = WS.Worker_Name
  WHERE Age > 30;

SELECT Laptop.Speed, PC.Speed FROM Laptop INNER JOIN PC ON Laptop.Speed > PC.Speed;

SELECT P1.Model_No, P2.Model_No, P1.HD
  FROM PC P1 JOIN PC P2
  ON P1.HD = P2.HD
  WHERE P1.Model_No != P2.Model_No;

SELECT P.Maker, PC.* FROM Product_Info P JOIN PC ON P.Model_No = PC.Model_No;

SELECT PC.Model_No, Laptop.Model_No, PC.Price FROM PC JOIN Laptop ON PC.Price = Laptop.Price;

SELECT P.Model_No, PC.Model_No FROM Product_Info P LEFT OUTER JOIN PC ON P.Model_No = PC.Model_No;
SELECT PC.Model_No, P.Model_No FROM PC RIGHT OUTER JOIN Product_Info P ON P.Model_No = PC.Model_No;
SELECT PC.Model_No, L.Model_No FROM PC FULL OUTER JOIN Laptop L ON L.Model_No = PC.Model_No;

SELECT P.Model_No, NVL(PC.Model_No, 'Not a PC') "PC Model No" FROM Product_Info P LEFT OUTER JOIN PC ON P.Model_No = PC.Model_No;