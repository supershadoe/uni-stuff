<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Exercise 8d</title>
    <style>
        body {
            background-color: powderblue;
            font-family: 'Calibri';
            font-size: 25px;
        }
        input {
            font-family: inherit;
            font-size: inherit;
            border-radius: 8px;
            padding: 8px 16px;
            margin-left: 12px;
            border: 0;
        }
        input[type=submit] {
            font-family: inherit;
            font-size: 20px;
            padding: 8px 16px;
            border-radius: 12px;
        }
        input[type=submit]:hover {
            background-color: #DDDDDD;
        }
    </style>
</head>
<body>
    <form method="post" action="">
        <label for="num">Enter a num</label>
        <input type="number" id="num" name="num" required />
        <input type="submit" value="Submit" />
    </form>
    <br />

    <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $num = $_POST["num"];
            if ($num >= 0 && $num <= 100) {
                echo "$num is in the range";
            } else {
                echo "$num is not in the range";
            }
        }
    ?>
</body>
</html>