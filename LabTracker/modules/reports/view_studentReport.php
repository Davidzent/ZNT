<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 8/13/21 9:39 PM
     */
    ?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>

<body id="<?= $data['_id']?>">
<?php include CORE_PATH . 'assets/inc/header.php'; ?>
<section id="main">
    <table class="dataTable">
        <thead>
        <tr>
            <td>Student Id</td>
            <td>Student Name</td>
            <td>Class</td>
            <td>Section #</td>
            <td>Time In</td>
            <td>Time Out</td>
            <td>Session</td>
            <td>Running Total</td>
        </tr>
        </thead>
        <tbody>
        <?php
            foreach ($data['data'] as $k => $v){
                $name = $v[0]['class'];
                $running = 0;
                echo "<tr><td colspan='8'>Section number: $k - $name</td></tr>";
                foreach ( $v as $item ) {

                    echo "<tr>";
                    echo "<td>${item['sid']}</td>";
                    echo "<td>" . ucwords( strtolower( $item['lname'] .', '. $item['fname']) ) . "</td>";
                    echo "<td>${item['class']}</td>";
                    echo "<td>${item['section']}</td>";
                    echo "<td>" . Time::humanDate( $item['timein'] ) . "</td>";
                    echo "<td>" . Time::humanDate( $item['timeout'] ) . "</td>";
                    echo "<td>" . Time::getTimeChunksFromSeconds( $item['sum'], true, 'hms' ) . "</td>";
                    $running += $item['sum'];
                    echo "<td>" . Time::getTimeChunksFromSeconds( $running, true, 'hms' ) . "</td>";
                    echo "</tr>";

                }
                echo "<tr><td colspan='8' class='alignrightImp'>Total time: " . Time::getTimeChunksFromSeconds( $running, true, 'hms' ) . "</td></tr>";
            }
        ?>
        </tbody>
    </table>
</section>
<?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>

</html>
