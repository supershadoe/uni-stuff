<?php
    session_start();
    $user_details = array();
    $conn = new mysqli("localhost", "lab_user", "hello123", "banking_system");
    if (! $conn) {
        die("Failed to connect to database.");
    }
    if (! isset($_SESSION["auth"])) {
        header("Location: login.php");
    } else {
        $sql = "SELECT username, balance FROM customers WHERE customer_id = '".$_SESSION["auth"]."';";
        $res = $conn->query("SELECT username, balance FROM customers WHERE customer_id = '".$_SESSION["auth"]."';");
        $user_details = $res->fetch_assoc();
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard | XYZ Bank</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <nav>
        <div>
            XYZ BANK
        </div>
        <div>
            <div><a href="deposit.php">Deposit</a></div>
            <div><a href="withdraw.php">Withdraw</a></div>
            <div><a href="logout.php">Sign out</a></div>
        </div>
    </nav>
    <main>
        <div class="text-2xl">
            Hello, <span class="text-medium"><?php echo $user_details["username"] ?></span>.
        </div>
        <div class="text-xl">
            Your account balance is $<span class="text-medium">
                <?php echo $user_details["balance"] ?>
            </span>
        </div>
        <div class="text-2xl">
            Your most recent transactions are as follows.
        </div>
        <?php
            $customer_id = $_SESSION["auth"];
            $res = $conn->query("SELECT transaction_id, transaction_type, amount, transaction_date FROM transactions WHERE customer_id = '$customer_id' ORDER BY transaction_date DESC LIMIT 10");

            if ($res->num_rows == 0) {
        ?>
        <div>No recent transaction.</div>
        <?php } else { ?>
        <table>
            <thead>
                <tr>
                    <th>Txn id</th>
                    <th>Txn type</th>
                    <th>Amount</th>
                    <th>Date</th>
                </tr>
            </thead>
            <tbody>
                <?php
                    for ($i = 0; $i < $res->num_rows; $i++) {
                        $row = $res->fetch_assoc();
                ?>
                <tr>
                    <td><?php echo $row["transaction_id"] ?></td>
                    <td><?php echo $row["transaction_type"] ?></td>
                    <td>$<?php echo $row["amount"] ?></td>
                    <td><?php echo $row["transaction_date"] ?></td>
                </tr>
                <?php } ?>
            </tbody>
        </table>
        <?php } ?>
</body>
</html>
