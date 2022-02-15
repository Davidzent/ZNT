<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 6/17/21 6:59 PM
     */

    class students extends module {
    	const MAX_SESSION_TIME = 3;
        /**
         * @inheritDoc
         */
        public function fetch( $options = array() ) {
            $options = Core::getOptions( [
                'fields' => '*',
                'where' => '',
                'params' => [],
                'page' => 1,
                'limit' => -1
            ], $options );

            //for pagination the model will handle the rest of the query
            if( $options['limit'] != -1 ){
                $offset = ( $options['page'] - 1 ) * $options['limit'];
                $options['limit'] = $offset . ',' . $options['limit'];
            } else{
                unset( $options['limit'] );
            }

            return $this->model->get( $options );
        }

        public function fetchOne( $options = [] ){
            $options = Core::getOptions( array(
                'sid' => -1,
                'fields' => '*',
                'where' => '',
                'params' => array()
            ), $options );

            if ( $options['id'] != -1 ) {
                $options['where'] = 'id=?';
                array_push( $options['params'], $options['id'] );
            }

            $item = $this->model->getOne( $options );
            return $item;
        }

        public function fetchStudentCourses( $options = [] ){
            $options = Core::getOptions( [
                'sid' => -1,
                'verified' => -1,
                'fields' => 'sc.*, c.section,c.term, s.fname,s.lname',
                'where' => '',
                'params' => [],
                'table' => 'studentXcourses as sc inner join courses as c on sc.sectionID = c.id inner join students as s on sc.sid=s.id'
            ], $options );

            if ($options['sid']!=-1&&$options['verified']!=-1) {
                $options['fields'] = 'sid, c.*';
                $options['where'] = 'sid=? && verified=? && c.term=?';
                array_push( $options['params'], $options['sid'] );
                array_push( $options['params'], $options['verified'] );
                array_push( $options['params'], $options['term'] );
            }

            else if ($options['sid']!=-1) {
                $options['fields'] = 'sc.sid, c.*';
                $options['where'] = 'sc.sid=?';
                $options['params'][] = $options['sid'];
            }

            $courses = $this->model->get( $options );
            return $courses;
        }
        public function fetchStudentsInCourse( $options = [] ){
            $options = Core::getOptions( [
                'section' => -1,
                'fields' => 's.id',
                'where' => '',
                'params' => [],
                'table' => 'studentXcourses as s inner join courses as c on s.sectionID = c.id'
            ], $options );

            if ($options['sectionID']!=-1) {
                $options['fields'] = 's.id';
                $options['where'] = 's.sectionID=?';
                $options['params'][] = $options['sectionID'];
            }
            else if ($options['sid']!=-1) {
                $options['fields'] = 's.id';
                $options['where'] = 's.sid=?';
                $options['params'][] = $options['sid'];
            }
            $courses = $this->model->get( $options );
            return $courses;
        }
        
        public function fetchStudentVerify( $options = [] ){
            $options = Core::getOptions( [
                'fields' => 'sc.* , s.fname,s.lname, c.section ',
                'where' => '',
                'params' => [],
                'table' => 'studentXcourses as sc inner join courses as c on sc.sectionID = c.id inner join students as s on sc.sid=s.id',
                'order' => 'c.section, sc.sid, s.fname, s.lname'
            ], $options );

            if (isset($options['verified'])&&$options['verified']!=-1) {
                $options['where'] = 'verified=?';
                $options['params'][] = $options['verified'];
            }
            $courses = $this->model->get( $options );
            return $courses;
        }
        
        public function fetchActiveStudents( $options = []){
            $options = Core::getOptions( [
                'fields' => 'tm.id,tm.sid,tm.timein,tm.timeout,c.id as sectionID,tm.term, c.section, s.fname,s.lname',
                'params' => [],
                'table' => 'timeLogs as tm inner join students as s on tm.sid=s.id inner join courses as c on tm.section=c.id WHERE tm.timeout IS NULL',
                'order' => 'c.section, tm.sid, s.fname, s.lname'
            ], $options );
            $courses = $this->model->get( $options );
            return $courses;
        }
        
        public function fetchTimeLogs( $options = []){
            $options = Core::getOptions( [
                'section' => -1,
                'timeout' => -1,
                'fields' => 'tm.id,tm.sid,tm.timein,tm.timeout,c.id as sectionID,tm.term, c.section, s.*',
                'params' => [],
                'where' => '',
                'table' => 'timeLogs as tm inner join students as s on tm.sid=s.id inner join courses as c on tm.section=c.id',
                'order' => 'tm.timein, tm.timeout,c.section, tm.sid'
            ], $options );
            
            //timelogs not completed where section = section
            if (isset($options['section'])&&$options['section']!=-1&&$options['timeout']===false) {
                $options['fields'] = 'tm.id';
                $options['where'] = 'c.section=? && (timeout=-1 || timeout is null)';
                $options['params'][] = $options['section'];
            }
            //timelogs completed where section = section
            else if (isset($options['section'])&&$options['section']!=-1&&$options['timeout']===true) {
                $options['fields'] = 'tm.id';
                $options['where'] = 'c.section=? && timeout!=-1 && timeout is not null';
                $options['params'][] = $options['section'];
            }
            //timelogs where section = section
            else if (isset($options['section'])&&$options['section']!=-1) {
                $options['fields'] = 'tm.id';
                $options['where'] = 'c.section=?';
                $options['params'][] = $options['section'];

            }
            //timelogs not completed
            else if($options['timeout']===false){
                $options['fields'] = 'tm.id,tm.sid,tm.timein,tm.timeout,c.id as sectionID,tm.term, c.section, s.fname, s.lname';
                $options['where'] = 'timeout=? || timeout is null';
                $options['params'][] = -1;
            }
            //timelogs completed
            else if($options['timeout']===true){
                $options['fields'] = 'tm.id,tm.sid,tm.timein,tm.timeout,c.id as sectionID,tm.term, c.section, s.fname, s.lname';
                $options['where'] = 'timeout!=? && timeout is not null';
                $options['params'][] = -1;
            }
            //timelogs where sid=sid
            else if($options['sid']!=-1){
                $options['fields'] = 'tm.id';
                $options['where'] = 'sid=?';
                $options['params'][] = $options['sid'];
            }
            $courses = $this->model->get( $options );
            return $courses;
        }
        
        
                
        public function fetchCourses( $options = []){
            $options = Core::getOptions( [
                'fields' => '*',
                'params' => [],
                'table' => 'courses',
                'order' => 'section, name, professor'
            ], $options );
            $courses = $this->model->get( $options );
            return $courses;
        }
        public function fetchOneTerm( $options = [] ){
            $options = Core::getOptions( array(
                'current'=>-1,
                'term'=>-1,
                'table' => 'terms',
                'fields' => 'term',
                'where' => '',
                'params' => array()
            ), $options );

            if ( $options['current'] != -1 ) {
                $options['where'] = 'current=?';
                array_push( $options['params'], $options['current'] );
            }

            $courses = $this->model->getOne( $options );
            return $courses;
        }
        public function fetchOneCourse( $options = [] ){
            $options = Core::getOptions( array(
                'current'=>-1,
                'id'=>-1,
                'section'=>-1,
                'term'=>-1,
                'table' => 'courses',
                'fields' => '*',
                'where' => '',
                'params' => array()
            ), $options );

            if ( $options['section'] != -1 && $options['term'] != -1) {
                $options['where'] = 'section=? && term=?';
                array_push( $options['params'], $options['section'] );
                array_push( $options['params'], $options['term'] );
            }
            else if ( $options['id'] != -1) {
                $options['fields'] = 'section';
                $options['where'] = 'id=?';
                array_push( $options['params'], $options['id'] );
            }

            $courses = $this->model->getOne( $options );
            return $courses;
        }
        
        public function SendOneStudent( $options = [] ){
            //*****************************************
            //Insert the Student into the student table
            //*****************************************
            $options = Core::getOptions( array(
                'table' => 'students',
                'fields' => 'id,fname,lname',
                'params' => array()
            ), $options );

            if ( $options['sid'] != -1 ) {
                
                array_push( $options['params'], $options['sid'] );
            }if ( $options['fname'] != -1 ) {
                
                array_push( $options['params'], $options['fname'] );
            }if ( $options['lname'] != -1 ) {
                
                array_push( $options['params'], $options['lname'] );
            }
 
            return $this->model->insertOne( $options );
        }
        public function SendOneCourse( $options = [] ){
            //*****************************************
            //Insert the Student into the student table
            //*****************************************
            $options = Core::getOptions( array(
                'table' => 'courses',
                'fields' => 'section,name,professor',
                'params' => array()
            ), $options );

            if ( $options['section'] != -1 ) {
                
                array_push( $options['params'], $options['section'] );
            }if ( $options['name'] != -1 ) {
                
                array_push( $options['params'], $options['name'] );
            }if ( $options['professor'] != -1 ) {
                
                array_push( $options['params'], $options['professor'] );
            }
 
            return $this->model->insertOne( $options );
        }
        public function SendOneStudentXCourses( $options = [] ){
            //*******************************************
            //Insert the Student into the studentxcourses
            //*******************************************
            $options = Core::getOptions( array(
                'sid' => -1,
                'sectionID' => -1,
                'verified' => -1,
                'table' => 'studentXcourses',
                'fields' => 'sid,sectionID,verified',
                'params' => array()
            ), $options );

            if ( $options['sid'] != -1 ) {
                
                array_push( $options['params'], $options['sid'] );
            }if ( $options['sectionID'] != -1 ) {
                
                array_push( $options['params'], $options['sectionID'] );
            }
            if ( $options['verified'] != -1 ) {
                
                array_push( $options['params'], $options['verified'] );
            }
            $item = $this->model->insertOne( $options );
            return $item;
        }
        
        //Validate students classes
        private function ValidateOne( $options = []){
            $options = [
                'table' => 'studentXcourses',
                'update' => 'verified=?',
                'where' => 'id=?',
                'params' => [ 1, $options['id'] ]
            ];
            $result = $this->model->update( $options );
            return $result;
        }
        
        //Edit student Time logs
        private function EditTimelogs( $options = []){
            $options = Core::getOptions( array(
                'section'=>-1,
                'newsection'=>-1,
                'id'=>-1,
                'sid'=>-1,
                'timein'=>-1,
                'timeout'=>-1,
                'newsid'=>-1,
                'table' => 'timeLogs',
                'update' => '',
                'where' => 'id=?',
                'params' => []
            ), $options );
            
            if ( $options['section'] != -1 && $options['id'] != -1) {
                $options['update'] = 'section=?';
                array_push( $options['params'], $options['section'] );
                array_push( $options['params'], $options['id'] );

            }
            if ( $options['section'] != -1 && $options['newsection'] != -1 && $options['sid'] != -1) {
                $options['update'] = 'section=?';
                $options['where'] = 'section=? && sid=?';
                array_push( $options['params'], $options['newsection'] );
                array_push( $options['params'], $options['section'] );
                array_push( $options['params'], $options['sid'] );
            }
            else if ( $options['sid'] != -1  && $options['id'] != -1) {
                $options['update'] = 'sid=?';
                array_push( $options['params'], $options['sid'] );
                array_push( $options['params'], $options['id'] );

            }
            else if ( $options['timein'] != -1 ) {
                $options['update'] = 'timein=?';
                array_push( $options['params'], $options['timein'] );
                array_push( $options['params'], $options['id'] );
            }
            else if ( $options['timeout'] != -1 ) {
                $options['update'] = 'timeout=?';
                array_push( $options['params'], $options['timeout'] );
                array_push( $options['params'], $options['id'] );
            }
            else if ( $options['newsid'] != -1&&$options['sid'] != -1) {
                $options['update'] = 'sid=?';
                array_push( $options['params'], $options['newsid'] );
                array_push( $options['params'], $options['sid'] );
            }
            else if ( $options['newsection'] != -1&&$options['section'] != -1) {
                $options['update'] = 'section=?';
                $options['where'] = 'section=?';
                array_push( $options['params'], $options['newsection'] );
                array_push( $options['params'], $options['section'] );
            }


            $result = $this->model->update( $options );
            return $result;
        }

        //Edit course
        private function EditCourse( $options = []){
            $options = Core::getOptions( array(
                'section' => -1,
                'term' => -1,
                'professor' => -1,
                'sectionnew' => -1,
                'name' => -1,
                'table' => 'courses',
                'update' => '',
                'where' => 'section=? && term=?',
                'params' => []
            ), $options );

            if($options['section'] != -1 && $options['term'] != -1){
                if ( $options['professor'] != -1 ) {
                    $options['update'] = 'professor=?';
                    array_push( $options['params'], $options['professor'] );
                    array_push( $options['params'], $options['section'] );
                    array_push( $options['params'], $options['term'] );
                }
                else if ( $options['sectionnew'] != -1 ) {
                    $options['update'] = 'section=?';
                    array_push( $options['params'], $options['sectionnew'] );
                    array_push( $options['params'], $options['section'] );
                    array_push( $options['params'], $options['term'] );
                }
                else if ( $options['name'] != -1 ) {
                    $options['update'] = 'name=?';
                    array_push( $options['params'], $options['name'] );
                    array_push( $options['params'], $options['section'] );
                    array_push( $options['params'], $options['term'] );
                }
            }
            

            $result = $this->model->update( $options );
            return $result;
        }
        //Edit course
        private function EditStudent( $options = []){
            $options = Core::getOptions( array(
                'id' => -1,
                'fname' => -1,
                'lname' => -1,
                'newid' => -1,
                'table' => 'students',
                'update' => '',
                'where' => 'id=?',
                'params' => []
            ), $options );

            if ( $options['newid'] != -1 && $options['id'] != -1) {
                $options['update'] = 'id=?';
                array_push( $options['params'], $options['newid'] );
                array_push( $options['params'], $options['id'] );
            }
            else if ( $options['fname'] != -1 && $options['id'] != -1 ) {
                $options['update'] = 'fname=?';
                array_push( $options['params'], $options['fname'] );
                array_push( $options['params'], $options['id'] );
            }
            else if ( $options['lname'] != -1 && $options['id'] != -1) {
                $options['update'] = 'lname=?';
                array_push( $options['params'], $options['lname'] );
                array_push( $options['params'], $options['id'] );
            }

            $result = $this->model->update( $options );
            return $result;
        }
        //Edit One studentXcourses
        private function EditStudentCourse( $options = []){
            $options = Core::getOptions( array(
                'id' => -1,
                'sid' => -1,
                'sectionID' => -1,
                'newsid' => -1,
                'table' => 'studentXcourses',
                'update' => '',
                'where' => '',
                'params' => []
            ), $options );
            if($options['sectionID']!=-1&&$options['id']!=-1){
                $options['update'] = 'sectionID=?';
                $options['where'] = 'id=?';
                array_push( $options['params'], $options['sectionID'] );
                array_push( $options['params'], $options['id'] );
            }
            else if($options['sid']!=-1&&$options['id']!=-1){
                $options['update'] = 'sid=?';
                $options['where'] = 'id=?';
                array_push( $options['params'], $options['sid'] );
                array_push( $options['params'], $options['id'] );
            }
            else if($options['newsid']!=-1&&$options['sid']!=-1){
                $options['update'] = 'sid=?';
                $options['where'] = 'sid=?';
                array_push( $options['params'], $options['newsid'] );
                array_push( $options['params'], $options['sid'] );
            }
            else if($options['newsection']!=-1&&$options['section']!=-1){
                $options['update'] = 'sectionID=?';
                $options['where'] = 'section=?';
                array_push( $options['params'], $options['newsection'] );
                array_push( $options['params'], $options['section'] );
            }
            $result = $this->model->update( $options );
            return $result;
        }
        //Delete One student Record
        private function DelStudentRecord( $options = []){
            $options = [
                'id' => -1,
                'table' => 'timeLogs',
                'where' => 'id=?',
                'params' => [$options['id']]
            ];
            $result = $this->model->delete( $options );
            return $result;
        }
        //Delete One studentXcourses
        private function DelStudentCourse( $options = []){
            $options = Core::getOptions( array(
                'id' => -1,
                'sid' => -1,
                'section' => -1,
                'table' => 'studentXcourses',
                'where' => '',
                'params' => []
            ), $options );
            if($options['id']!=-1){
                $options['where'] = 'id=?';
                array_push( $options['params'], $options['id'] );
            }
            else if($options['sid']!=-1){
                $options['where'] = 'sid=?';
                array_push( $options['params'], $options['sid'] );
            }
            else if($options['section']!=-1){
                $options['where'] = 'section=?';
                array_push( $options['params'], $options['section'] );
            }
            $result = $this->model->delete( $options );
            return $result;
        }
        //Delete One Section
        private function DelCourse( $options = []){
            $options = [
                'id' => -1,
                'table' => 'courses',
                'where' => 'section=?',
                'params' => [$options['section']]
            ];
            $result = $this->model->delete( $options );
            return $result;
        }
        //Delete One Student
        private function DelStudent( $options = []){
            $options = [
                'table' => 'students',
                'where' => 'id=?',
                'params' => [$options['id']]
            ];
            $result = $this->model->delete( $options );
            return $result;
        }

        /**
         * Edit Students Classes or remove if specified
         * The ID is the unique key of Courses
         * @param $sv array
         * @return string
         */

        public function EditStudentsClasses($edit,$remove){
            $errors="";
            //Delete the Sections
            if($remove){
                foreach( $remove as $key=>$item){
                    $students=$this->DelStudentCourse(['id'=>$item]);
                    if($students===false){
                        $errors.="Error removing the Student Class for student: ".$_POST['sid'][$key]." Section: ".$_POST['section'][$key]."<br>";
                    }
                }
            }
            //Update the Sections
            if($edit){
                foreach( $edit as $key => $item){
                    $student=$this->fetchOne(['id'=>$item,'table'=>'studentXcourses']);
                    $student=$this->fetchOne(['id'=>$item,'table'=>'studentXcourses']);
                    if(strlen($_POST['section'][$key])==5&&$_POST['section'][$key]!=$student['section']&&!empty($_POST['section'][$key])){
                        $term=$this->fetchOneTerm(['current'=>1]);
                        $SXsection=$this->fetchOneCourse(['id'=>$student['sectionID']]);
                        $section=$this->fetchOneCourse(['section'=>$_POST['section'][$key],'term'=>$term['term']]);
                        if($section===false){
                            $errors.="The new section: ".$_POST['section'][$key]." does not exist for the student: ".$student['sid']." and Section: ".$student['section']."<br>";
                        }else{
                            $sectionlogs=$this->EditTimelogs( ['sid'=>$student['sid'],'section'=>$SXsection['section'],'newsection'=>$_POST['section'][$key]]);
                            if($sectionlogs===false){
                                $errors.="The Student Logs for section".$_POST['section'][$key]." was not send due to an error.<br>";
                            }
                            $temp=$this->EditStudentCourse(['sectionID'=>$section['id'],'id'=>$item]);
                            if($temp===false){
                                $errors.="The new section ".$_POST['section'][$key]." was not send due to an error for the student: ".$student['sid']." and Section: ".$student['section']."<br>";
                            }
                        }
                    }
                    else if(strlen($_POST['section'][$key])!=5){
                        $errors.="<br>Error the section should be 5 digits for section: ".$student['section']." and Student:".$student['sid']." Entered: ".$_POST['section'][$key]."<br>";
                    }
                    if(strlen($_POST['sid'][$key])==7&&$_POST['sid'][$key]!=$student['sid']&&!empty($_POST['sid'][$key])){
                        $temp=$this->EditStudentCourse(['sid'=>$_POST['sid'][$key],'id'=>$item]);
                        if($temp===false){
                            $errors.="Error uptading the student id for student: ".$_POST['sid'][$key]."<br>";
                        }
                    }
                    else if(strlen($_POST['sid'][$key])!=7){
                        $errors.="<br>Error the student id should be 7 digits for student: ".$student['sid']." Entered: ".$_POST['sid'][$key]."<br>";
                    }
                }

            }
            //update the table
            return $this->StudentsClasses($errors);
        }

        /**
         * get all the sections
         * @return string
         */

        public function StudentsClasses($error){
            //check if there are sections to edit
            $Students = $this->fetchStudentCourses([]);

            if( $Students ){
                //There are StudentsXcourses in the database
                return Ajax::response(['studentclasses' => $Students,'errors'=>$error], true, "The Edit Was Successful.");
            } else {
                //There are no StudentsXcourses to be edited
                return Ajax::response([], false, "There are no students in Classes to be edit.");
            }
        }

        /**
         * Edit Students or remove if specified
         * The ID is the unique key of Courses
         * @param $sv array
         * @return string
         */
        public function EditStudents($edit,$remove){
            $errors="";
            //Delete the Students
            if($remove){
                foreach( $remove as $item){
                    $students=$this->DelStudentCourse(['sid'=>$item]);
                    if($students===false){
                        $errors.="Error removing the student courses for student: ".$item."<br>";
                    }
                    $u=$this->DelStudent( ['id'=>$item]);
                    if($u===false){
                        $errors.="Error removing the section: ".$item."<br>";
                    }
                }
            }
            //Update the Students
            if($edit){
                foreach( $edit as $key => $item){
                    $student=$this->fetchOne(['id'=>$item]);
                    if($_POST['fname'][$key]!=$student['fname']&&!empty($_POST['fname'][$key])){
                        $temp=$this->EditStudent(['fname'=>$_POST['fname'][$key],'id'=>$item]);
                        if($temp===false){
                            $errors.="<br>Error uptading the student first name for student: ".$item."<br>";
                        }
                    }
                    if($_POST['lname'][$key]!=$student['lname']&&!empty($_POST['lname'][$key])){
                        $temp=$this->EditStudent(['lname'=>$_POST['lname'][$key],'id'=>$item]);
                        if($temp===false){
                            $errors.="Error uptading the last name for student: ".$item."<br>";
                        }
                    }
                    if(strlen($_POST['id'][$key])==7&&$_POST['id'][$key]!=$student['id']&&!empty($_POST['id'][$key])){
                        $temp=$this->EditStudent(['newid'=>$_POST['id'][$key],'id'=>$item]);
                        if($temp===false){
                            $errors.="<br>Error uptading the Student ID for student (no changes done): ".$item."<br>";
                        }else{
                            $studentXcourse=$this->EditStudentCourse(['sid'=>$item,'newsid'=>$_POST['id'][$key]]);
                            if($studentXcourse===false){
                                $errors.="<br>Error uptading the student course for the student: ".$item."<br>";
                            }
                            $studentlog=$this->EditTimelogs(['sid'=>$item,'newsid'=>$_POST['id'][$key]]);
                            if($studentlog===false){
                                $errors.="<br>Error uptading the timelogs for the student: ".$item."<br>";
                            }
                        }
                    }else if(strlen($_POST['id'][$key])!=7){
                        $errors.="<br>Error the student id should be 7 digits for student: ".$item." Entered: ".$_POST['id'][$key]."<br>";
                    }


                }

            }
            //update the table
            return $this->listing($errors);
        }

        /**
         * get all the Students
         * @return string
         */
        public function listing($error){
            //check if there are Students to edit
            $Students = $this->fetch([]);
            if( $Students ){
                //There are students in the database
                return Ajax::response(['students' => $Students,'errors'=>$error], true, "The Edit Was Successful.");
            } else {
                //There are no students to be edit
                return Ajax::response([], false, "There are no students to be edit.");
            }
        }
        /**
         * Edit Sections or remove if specified
         * The ID is the unique key of Courses
         * @param $sv array 
         * @return string
         */
        
        public function EditSections($edit,$remove){
            $errors="";
            //Delete the Sections
            if($remove){
                foreach( $remove as $item){
                    $students=$this->DelStudentCourse(['section'=>$item]);
                    if($students===false){
                        $errors.="Error removing the student courses for course: ".$item."<br>";
                    }
                    $u=$this->DelCourse( ['section'=>$item]);
                    if($u===false){
                        $errors.="Error removing the section: ".$item."<br>";
                    }
                }
            }
            //Update the Sections
            if($edit){
                foreach( $edit as $key => $item){
                    $term=$this->fetchOneTerm(['current'=>1]);
                    $course=$this->fetchOneCourse(['section'=>$item,'term'=>$term['term']]);
                    if($_POST['professor'][$key]!=$course['professor']&&!empty($_POST['professor'][$key])){
                        $temp=$this->EditCourse(['professor'=>$_POST['professor'][$key],'section'=>$item,'term'=>$term['term']]);
                        if($temp===false){
                            $errors.="<br>Error uptading the professor for section: ".$item."<br>";
                        }
                    }
                    
                    if(strlen($_POST['section'][$key])==5&&$_POST['section'][$key]!=$course['section']&&!empty($_POST['section'][$key])){
                        $temp=$this->EditCourse(['sectionnew'=>$_POST['section'][$key],'section'=>$item,'term'=>$term['term']]);
                        if($temp===false){
                            $errors.="<br>Error updating the section for section: ".$item."<br>";
                        }else{
                            $newcourse=$this->fetchOneCourse(['section'=>$_POST['section'][$key],'term'=>$term['term']]);
                            $studentXcourse=$this->EditStudentCourse(['section'=>$item,'newsection'=>$newcourse['id']]);
                            if($studentXcourse===false){
                                $errors.="<br>Error uptading the student course for the course: ".$_POST['section'][$key]."<br>";
                            }
                            //don't need to update this now i think. Confirmed not need to update. using a reference now
//                            $studentlog=$this->EditTimelogs(['section'=>$item,'newsection'=>$_POST['section'][$key]]);
//                            if($studentlog===false){
//                                $errors.="<br>Error uptading the timelogs for the section: ".$_POST['section'][$key]."<br>";
//                            }
                        }
                    }else if(strlen($_POST['section'][$key])!=5){
                        $errors.="<br>Error the section should be 5 digits for section: ".$item." Entered: ".$_POST['section'][$key]."<br>";
                    }

                    if($_POST['name'][$key]!=$course['name']&&!empty($_POST['name'][$key])){
                        $temp=$this->EditCourse(['name'=>$_POST['name'][$key],'section'=>$item,'term'=>$term['term']]);
                        if($temp===false){
                            $errors.="Error uptading the name for section: ".$item."<br>";
                        }
                    }
                }

            }
            //update the table
            return $this->Sections($errors);
        }
        
        /**
         * get all the sections
         * @return string
         */
        
        public function Sections($error){
            //check if there are sections to edit
            $sections = $this->fetchCourses([]);
            if( $sections ){

                foreach ($sections as $key=>$item){
                    //counts the students and logs
                    $sections[$key]['countStudents']=count($this->fetchStudentsInCourse(['sectionID'=>$item['id']]));
                    $sections[$key]['countComplete']=count($this->fetchTimeLogs(['section'=>$item['section'],'timeout'=>true]));
                    $sections[$key]['countIncomplete']=count($this->fetchTimeLogs(['section'=>$item['section'],'timeout'=>false]));
                }

                //There are sections in the database
                return Ajax::response(['classes' => $sections,'errors'=>$error], true, "The Edit Was Successful.");
            } else {
                //There are no students to be verified
                return Ajax::response([], false, "There are no sections to be edit.");    
            }
        }
        
        /**
         * Edit Students if specified
         * The ID is the unique key of timeLogs
         * @param $sv array 
         * @return string
         */
        
        public function EditStudentsLogs($edit,$remove,$times){
            $errors="";
            //Delete the students
            if($remove){
                foreach( $remove as $item){
                    $u=$this->DelStudentRecord( ['id'=>$item]);
                    if($u===false){
                        return Ajax::response([], false, "There was an issue deleting a student record");    
                    }
                }
            }
            //Update the students
            if($edit){
                foreach( $edit as $key => $item){
                    $timein=-1;
                    $timeout=-1;
					if ( $_POST[ 'timein' ][ $key ] != "No Entrance"
						&& !empty( $_POST[ 'timein' ][ $key ] )
						&& $_POST[ 'timeout' ][ $key ] != "No Logout"
						&& !empty( $_POST[ 'timeout' ][ $key ] )
					) {
                        $timein=strtotime($_POST['timein'][$key]);
                        $timeout=strtotime($_POST['timeout'][$key]); 
                        if($timein>$timeout){
                            $errors.="The log in time cannot be greater than the log out time in section:".$_POST['section'][$key]."<br>";   
                        }
                        else{
                            $timein=strtotime($_POST['timein'][$key]);
                            $in=$this->EditTimelogs( ['id'=>$item,'timein'=>$timein]);
                            if($in===false){
                                $errors.="There was an issue editing a student time in section: ".$_POST['section'][$key]."<br>";    
                            }
                            $timeout=strtotime($_POST['timeout'][$key]); 
                            $out=$this->EditTimelogs( ['id'=>$item,'timeout'=>$timeout]);
                            if($out===false){
                                $errors.="There was an issue editing a student time out section: ".$_POST['section'][$key]."<br>";        
                            }
                        }
                    }
                    else if($_POST['timein'][$key]!="No Entrance"&&!empty($_POST['timein'][$key])){
                        $timein=strtotime($_POST['timein'][$key]);
                        $in=$this->EditTimelogs( ['id'=>$item,'timein'=>$timein]);
                        if($in===false){
                            $errors.="There was an issue editing a student time in for student: ";    
                        }
                    }
                    else if($_POST['timeout'][$key]!="No Logout"&&!empty($_POST['timeout'][$key])){
                        $timeout=strtotime($_POST['timeout'][$key]); 
                        $out=$this->EditTimelogs( ['id'=>$item,'timeout'=>$timeout]);
                        if($out===false){
                            $errors.="There was an issue editing a student time out section: ".$_POST['section'][$key]."<br>";        
                        }
                    }
                    if(strlen($_POST['section'][$key])==5&&!empty($_POST['section'][$key])){
                        $term=$this->fetchOneTerm(['current'=>1]);
                        $section=$this->fetchOneCourse(['section'=>$_POST['section'][$key],'term'=>$term['term']]);
                        if($section===false){
                            $errors.="The new section: ".$_POST['section'][$key]." does not exist <br>";
                        }else{
                            $section=$this->EditTimelogs( ['id'=>$item,'section'=>$section['id']]);
                            if($section===false){
                                $errors.="The new section".$_POST['section'][$key]." was not sent due to an error.<br>";
                            }
                        }
                    }
                    else if(strlen($_POST['section'][$key])!=5){
                        $errors.="<br>Error the section should be 5 digits for section: ".$item." Entered: ".$_POST['section'][$key]."<br>";
                    }
                }
            }

            return $this->StudentsTimeLogs($times,$errors);
        }
        
        /**
         * get all the students time logs
         * @return string
         */
        
        public function StudentsTimeLogs($times,$errors){
            //check if student exist
            $students = $this->fetchTimeLogs(['timeout'=>$times]);
            $id="";
            if($times){
                $id="EditReportsSubmit";
            }else{
                $id="EditIncompleteReportsSubmit";
            }
            if( $students ){
                //convert "timein" and "timeout" to human readable 
                foreach ( $students as $key => $item ){
                    if(!empty($item['timein'])&&$item['timein']!=-1&&isset($item['timein'])){
                        $delta = date("Y-m-d\TH:i" ,$item['timein']);
                        $students[$key]['timein']=$delta;
                    }
                    else{
                        $students[$key]['timein']="No Entrance";
                    }
                    if(!empty($item['timeout'])&&$item['timeout']!=-1&&isset($item['timeout'])){
                        $delta = Date("Y-m-d\TH:i" ,$item['timeout']);
                        $students[$key]['timeout']=$delta;
                        //$students[$key]['time']=strtotime($delta);
                    }
                    else{
                        $students[$key]['timeout']="No Logout";
                    }
                }
                //There are students in the database
                return Ajax::response(['students' => $students,'id'=>$id,'errors'=>$errors], true, "The Edit was successful.");
            } else {
                //There are no students to be verified
                return Ajax::response([], false, "There are no active students.");    
            }
        }
        
        /**
         * Logout students from the view active students if specified so
         * The ID is the unique key of timelogs
         * @param $sv array 
         * @return string
         */

		public function LogoutStudents( $sv ) {
			//Verify the students
			foreach ( $sv as $item ) {
//                $u=$this->voidRecord( ['id'=>$item], "", "" );
				$update = $this->model->update( [
					'update' => 'timeout=?',
					'params' => [ time() ],
					'id' => $item,
					'table' => 'timeLogs'
				] );
				if ( $update === false ) {
					return Ajax::response( [], false, "There was an issue logging out a student" );
				}
			}

			//update the table
			return $this->ActiveStudents();
		}
        
        /**
         * Search for students that are currently log on
         * @return string
         */
        
        public function ActiveStudents(){
            //check if student exist
            $students =  $this->fetchActiveStudents();
            //get the time delta
            $now = time();
            //get the time delta
            
            foreach ( $students as $key => $item ){
                $delta = ( $now - $item['timein'] );
                $students[$key]['time']=Time::getTimeChunksFromSeconds( $delta, true, "hm" );
                if(empty($students[$key]['time'])){
                    $students[$key]['time']="<1 minute";
                }
            }
            
            if( $students ){
                //There are students in the database
                return Ajax::response(['students' => $students], true, "The Students were logout successfully");
            } else {
                //There are no students to be verified
                return Ajax::response([], false, "There are no active students.");    
            }
        }
        
        
        /**
         * Verify students from an array of ids
         * The ID is the unique key of studentXcourses
         * @param $sv array 
         * @return string
         */
        
        public function ValidateStudents($sv){
            //Verify the students
            foreach( $sv as $item){
                $u=$this->ValidateOne(['id' => $item]);
                if($u===false){
                    return Ajax::response([], false, "There was an issue verifying a student.");
                }
            }
            
            //update the table
            return $this->studentNotVerified();

        }
        
        /**
         * Search for students that have not been verified
         * @return string
         */
        
        public function studentNotVerified(){
            //check if student exist
            $students = $this->fetchStudentVerify( ['verified' => 0 ] );
            
            if( $students ){
                //There are students in the database
                return Ajax::response(['students' => $students], true, "The students were verified successfully.");
            } else {
                //There are no students to be verified
                return Ajax::response([], false, "There are no students that need to be verified.");    
            }
        }
        
        /**
         * Add a student to a course
         * @param $sid string StudentID $section Class section number
         * @return string
         */
        
        public function AddCourse($sid,$section){
            $student = $this->fetchOne( ['id' => $sid ] );  
            if($student){
                $term=$this->fetchOneTerm(['current'=>1]);
                $course=$this->fetchOneCourse(['section'=>$section,'term'=>$term['term']]);
                if($course){
                    //check if the student is already in that class
                    //
                    $courses = $this->fetchStudentCourses( ['sid' => $sid] );   
                    $studentxcourse = false;                                  
                    foreach ( $courses as $item ) {                          
                        if($item['section']==$section){                         
                            $studentxcourse=true;
                        }
                    }
                    
                    if($studentxcourse){
                        return Ajax::response([], false, "You are already added to the course ");
                    }
                    
                    $studentX=$this->SendOneStudentXCourses(['sid' => $sid,'sectionID'=>$course['id'],'verified'=>1 ]); //This will be changed once the school goes back in person from 'sid' => $sid,'section'=>$section,'verified'=>1  to 'sid' => $sid,'section'=>$section 

                    if($studentX===false){
                        return Ajax::response([], false, 'Something went wrong sending the course with student sorry');      
                    }

                    return Ajax::response([ 'phase' => 2 ], true, 'You are now added to the class <br>section: '.$section.'<br>Class name: '.$course['name'].'<br>Professor: '.$course['professor']);
                }else{
                    return Ajax::response([], false, "There is no course with that section number please try again or talk with the front desk.");
                }
            }else{
                return Ajax::response([], false, "There is no student registered with that ID");
            }
            
        }
        
        /**
         * log time for the student when they register
         * @param $fname string first name $lname string last name $sid int student id 
         * @return string
         */
        
        public function studentRegister($fname,$lname,$sid,$section){
            //check if student exist
            $student = $this->fetchOne( ['id' => $sid ] );
            if( $student ){
                //This student already exist
                return Ajax::response([], false, 'This student id is already associated with an account.');                
            } else {
                $term=$this->fetchOneTerm(['current'=>1]);
                $course=$this->fetchOneCourse(['section'=>$section,'term'=>$term['term']]);
                if($course){                     
                    $student = $this->SendOneStudent( [ 'sid' => $sid,'fname' => $fname,'lname' => $lname] ); 
                    if($student===false){
                        return Ajax::response([], false, 'Something went wrong sending the student sorry');      
                    }
                    $studentX=$this->SendOneStudentXCourses(['sid' => $sid,'sectionID'=>$course['id'],'verified'=>1 ]); //This will be changed once the school goes back in person from 'sid' => $sid,'section'=>$section,'verified'=>1  to 'sid' => $sid,'section'=>$section 
                    
                    if($studentX===false){
                        return Ajax::response([], false, 'Something went wrong sending the course with student sorry');      
                    }
                    
                    return Ajax::response([ 'phase' => 2 ], true, 'Created student first name: '.$fname.' last name: '.$lname.' id: '.$sid.' in course section: '.$section.' course: '.$course['name'].".");
                }else{
                    return Ajax::response([], false, "There is no course with that section number please try again or talk with the front desk.");
                }
            }
        }
        
        /**
         * log time for the student when they enter the id
         * @param $sid int student id
         * @return string
         */
        public function studentEntered( $sid ){
            if( !$this->app->users->isLabOpen() ){
				return Ajax::response([], false, 'The lab is currently closed');
			}
            //are we logging out or in no double dipping allowed
            
            //check if student
            $term=$this->fetchOneTerm(['current'=>1]);
            $student = $this->fetchOne( ['id' => $sid ] );
            $courses = $this->fetchStudentCourses( [ 'sid' => $sid, 'verified'=>1, 'term'=>$term['term'] ] );
            if( $student ){
                //check if they have a session going now first
                $session = $this->isActiveSession( $sid );
                //got them
				//make sure they dont have an active session over the time limit
				if( $session !== false ){
					$delta = ( time() - $session['timein'] ) / Time::HOUR;
					if( $delta > self::MAX_SESSION_TIME ) { //if greater than 8 hours in one go void the record out
						//no longer voiding records past certain time
						//$voided = $this->voidRecord( $session, $sid, $activeCourse );
						$newLogout = $session['timein'] + ( self::MAX_SESSION_TIME * Time::HOUR );
						$voided = $this->setSession( $sid, false, $newLogout, $session['section'] );
						if( $voided ) $session = false;
					}
				}

                if ( $_POST[ 'phase' ] == '1' && $session === false ) {
                    //what course do we put them in?
                    if( count( $courses ) == 1){
                        //single course easy life
                        return $this->phase2Login( $session, $sid, $courses[0]['id'], $student, $courses );
                    } else if ( count( $courses ) > 1 ){
                        //get the current times in each of the courses
                        foreach ( $courses as $key => $item ) {
                            $courses[$key]['time'] = $this->getTotalTime( $sid, $item['id'], 'hm' );
                        }
                        
                        //multiple courses gotta pick
                        return Ajax::response( [ 'phase' => 1, 'courses' => $courses, 'sid' => $sid ], true, "Pick a class" );
                    } else {
                        //no courses?!?!?!?! #David: it is fine there are but just not verified... I hope
                        return Ajax::response( [], false, "No verified courses" );
                    }
                } else if ( $_POST[ 'phase' ] == '2' || isset( $session ) ) { //TODO isset should bere ?
                    if ( count( $courses ) == 1 ) {
                        //single course easy life
                        return $this->phase2Login( $session, $sid, $courses[0]['id'], $student, $courses );
                    } else {
                        if( isset( $_POST['course'] ) ) {
                            return $this->phase2Login( $session, $sid, $_POST[ 'course' ], $student, $courses );
                        } else if( isset( $session ) ){
                            return $this->phase2Login( $session, $sid, $session[ 'section' ], $student, $courses );
                        }
                    }
                }
            } else {
                //no such student
                return Ajax::response([], false, 'No student exists with that student id.');
            }
        }

		/**
		 * Voids out a record
		 * @param $session
		 * @param $sid
		 * @param $activeCourse
		 * @return bool
		 */
        private function voidRecord( $session, $sid, $activeCourse ){
            $options = [
                'table' => 'timeLogs',
                'update' => 'timeout=?',
                'where' => 'id=?',
                'params' => [ -1, $session['id'] ]
            ];
            $result = $this->model->update( $options );
            return $result;
        }

        private function phase2Login($session, $sid, $activeCourse, $student, $courses ){
            //TODO check course is exists for the user!
            //check if logged in
            $sesSet = false;
            //$session = $this->isActiveSession( $sid );
            $now = time();
            $loginData = [ 'phase' => 2, 'isLogin' => true ];
            if( MODE != 'local' ){
				$loginData['href'] = 'https://tinyurl.com/RCCCompLabFall2021';
				$loginData['action'] = 'newWindow';
			}

            $loginMsg = 'Session started<br>Opening zoom link in new window<br>click <a href="https://tinyurl.com/RCCCompLabFall2021">here to open</a>';
            
            if( $session !== false ){
                $sesSet = $this->setSession( $sid, false, $now, $activeCourse );
            } else {
                $sesSet = $this->setSession( $sid, true, $now, $activeCourse );
            }

            if( $sesSet ){
                if( $session !== false ){
                    $sessionTime = Time::getTimeChunks($session['timein'], $now, true);
                    $totalTime = $this->getTotalTime( $sid, $activeCourse );

                    return Ajax::response([ 'phase' => 2, 'isLogin' => false ], true, "Session ended. $sessionTime.<br/>Total time: $totalTime" );
                }
                //logged in
                return Ajax::response( $loginData, true, $loginMsg);
            } else {
                return Ajax::response([ 'phase' => 2, 'isLogin' => false ], false, 'An Error occurred try again');
            }
        }

        /**
         * checks if they have an active login in the lab
         * @param $sid int student id
         * @return array|bool
         */
        public function isActiveSession( $sid ){
            $options = [
                'table' => 'timeLogs',
                'where' => 'sid=? && timeout is null',
                'params' => [ $sid ]
            ];
            $d = $this->model->getOne( $options );
            return $d;
        }

        /**
         * logs the student into the lab
         * @param $sid int
         * @param $login bool
         * @param $now int
         * @param $course array
         * @return bool
         */
        public function setSession( $sid, $login, $now, $course ){
            if( $login ){
                $term=$this->fetchOneTerm(['current'=>1]);
                $options = [
                    'table' => 'timeLogs',
                    'fields' => 'sid,timein,section,term',
                    'params' => [ $sid, $now, $course,$term['term']]
                ];
                $result = $this->model->insertOne( $options );
                return $result === false ? false : true;
            } else {
                $options = [
                    'table' => 'timeLogs',
                    'update' => 'timeout=?',
                    'where' => 'sid=? && timeout is null',
                    'params' => [ $now, $sid ]
                ];
                $result = $this->model->update( $options );
                return $result;
            }
        }

        public function getTotalTime( $sid, $section, $timeUnits = 'hms' ){
            //SELECT id, sid, SUM(timeout - timein) FROM labtracker.timeLogs where timeout is not null;
            $options = [
                'table' => 'timeLogs',
                'fields' => 'id, sid, (timeout - timein) as sum',
                'where' => 'sid=? && timeout is not null && timeout != -1 && section=?',
                'params' => [ $sid, $section ]
            ];
            $d = $this->model->get( $options );
            if( isset( $d ) ){
                $sum = 0;
                foreach ( $d as $item ) {
                    $sum += $item['sum'];
                }

                return Time::getTimeChunksFromSeconds( $sum, true, $timeUnits );
            }
            else {
                return '0 seconds';
            }

        }
    }
