<?php
?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>
    <?php if( $GLOBALS['app']->users->isLoggedIn() ){ ?>
<body id="<?= $data['_id']?>">
    <?php include CORE_PATH . 'assets/inc/header.php';?>
    <section id="main">
        <div class="aligncenter">
            <div id="adminFormArea">
                <form id="ReportsAction" method="post" action="reports/report">
                    <input type="hidden" name="option" value="0"/>
                    <input type="hidden" name="phase" value="1"/>
                    <div class="errors"></div>
                    <div class="adminphase1">
                        <label>
                            <?php if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::REPORTS ) ) echo '<input id="TermReport" type="button" value="By Term" />' ?>
                            <?php if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::REPORTS ) ) echo '<input id="StudentReport" type="button" value="By Student (Total)" />' ?>
                            <?php if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::REPORTS ) ) echo '<input id="StudentReportDetails" type="button" value="By Student (Details)" />' ?>
                            <?php if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::REPORTS ) ) echo '<input id="DateReport" type="button" value="By Date Range" />' ?>
                            <?php if( Core::hasRole( users::ADMIN ) || Core::hasRole( users::REPORTS ) ) echo '<input id="SectionReport" type="button" value="By Class Section" />' ?>
                            
                        </label>
                    </div>
                    <div class="result"></div>
                    <div class="filters"></div>
                    <div class="adminphase2 none"></div>
                    <div class="adminphase2pages"></div>
                </form>

                

            </div>

        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
 <?php } ?>
</html>