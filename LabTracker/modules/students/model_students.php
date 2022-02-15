<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 7/4/21 3:29 PM
     */

    class model_students extends model_module{
        /**
         * insert a single student to the database
         * @param array $options
         * @return bool|int int of record inserted false if failed
         */
        public function InsertOneStudent( $options = [] ){
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
                array_push( $options['params'], strtolower( $options['fname'] ) );
            }if ( $options['lname'] != -1 ) {
                array_push( $options['params'], strtolower( $options['lname'] ) );
            }

            return $this->insertOne( $options );
        }

        /**
         * inserts a reference associating a student to a course
         * @param array $options
         * @return bool|int int of record inserted false if failed
         */
        public function InsertOneStudentXCourses( $options = [] ){
            //*******************************************
            //Insert the Student into the studentXcourses
            //*******************************************
            $options = Core::getOptions( array(
                'table' => 'studentXcourses',
                'fields' => 'sid,section',
                'params' => array()
            ), $options );

            if ( $options['sid'] != -1 ) {

                array_push( $options['params'], $options['sid'] );
            }if ( $options['section'] != -1 ) {

                array_push( $options['params'], $options['section'] );
            }
            $item = $this->insertOne( $options );
            return $item;
        }
    }
