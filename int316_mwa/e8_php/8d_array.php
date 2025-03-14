<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Exercise 8e</title>
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
        <label for="dat">Enter a value</label>
        <input id="dat" name="dat" required />
        <input type="submit" value="Check" />
    </form>
    <br />

    <?php
        $data = array(
            "car1" => "Ford",
            "car2" => "Suzuki",
            "car3" => "Hyundai",
        );
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $dat = $_POST["dat"];
            $found = false;
            foreach ($data as $k => $v) {
                if ($v == $dat) {
                    echo "$v was found in the array";
                    $found = true;
                    break;
                }
            }
            if (! $found) {
                echo "$dat was not found in the array";
            }
        }
    ?>
</body>
</html>