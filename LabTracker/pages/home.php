<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 6/17/21 3:51 PM
     */
	if( !$GLOBALS['app']->users->isLoggedIn() ) {
		if( !(Core::hasRole( users::ADMIN ) || Core::hasRole( users::VERIFY ) || Core::hasRole( users::REPORTS ) ) ) {
			Core::phpRedirect( 'users/kiosk');
		}
    }
	$opened = $GLOBALS['app']->users->isLabOpen()
?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>

    <style>

    </style>
</head>

<body>
    <?php include CORE_PATH . 'assets/inc/header.php';  ?>
    <section id="main">
        <div class="aligncenter">
            <div class="row wrap">
                <!-- <div class="splashLogo column">
                    <a href>
                        <i class="fas fa-laptop-house"></i>
                        <span>Remote</span>
                    </a>
                </div> -->
                <?php //if( $GLOBALS['app']->users->isLoggedIn() && Core::hasRole( users::KIOSK ) ){ ?>
                <div class="splashLogo column">
                    <a href="<?=CORE_URL?>users/kiosk">
                        <i class="fas fa-desktop"></i>
                        <span>Kiosk</span>
                    </a>
                </div>
                <?php
                 //}
                if( $GLOBALS['app']->users->isLoggedIn() ){
                    if( Core::hasRole( users::ADMIN ) ) {
                ?>
                    <div class="splashLogo column">
                        <a href="<?=CORE_URL?>create/data">
                            <i class="fas fa-folder-plus"></i>
                            <span>Create Data</span>
                        </a>
                    </div>
                <?php
                    }
                    if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::VERIFY ) ){
                ?>
                <div class="splashLogo column">
                    <a href="<?=CORE_URL?>users/admin">
                        <i class="fas fa-users-cog"></i>
                        <span>Admin</span>
                    </a>
                </div>
                <?php
                    }
                    if( Core::hasRole( users::REPORTS ) ) {
                ?>
                    <div class="splashLogo column">
                        <a href="<?=CORE_URL?>reports/report">
                            <i class="fas fa-clipboard-list"></i>
                            <span>Reports</span>
                        </a>
                    </div>
                
                <?php
                    }
                    if( Core::hasRole( users::ADMIN ) ){
                    ?>
                    <div class="splashLogo column">
                        <a href="<?=CORE_URL?>users/toggleLabOpen">
                            <i class="fas fa-power-off"></i>
                            <span><?= $opened ? 'Close ' : 'Open '?> Lab</span>
                        </a>
                    </div>
                    <?php
					}
                }
                ?>
            </div>
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>

</html>
