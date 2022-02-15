<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 6/17/21 4:54 PM
     */
?>
<!doctype html>
<html lang="en">
<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>
<body>
    <?php include CORE_PATH . 'assets/inc/header.php';  ?>
    <section id="main">
        <div class="aligncenter">
            <div class="kioskLogo">
                <img src="<?=CORE_URL?>assets/img/timer.png" width="127">
                <span>Lab Tracker</span>
            </div>
            <input class="margin10" type="text" name="id" placeholder="Student Id"/>
            
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
</html>

