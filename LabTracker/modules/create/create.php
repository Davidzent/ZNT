<?php
/**
 * Copyright (C) David Guijosa Infante - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by David Guijosa Infante <davidgin641@gmail.com>, 8/11/21 1:27 PM
 */


class create extends module {
    /**
     * @inheritDoc
     */
    public function fetch( $options = array() ) {
        // TODO: Implement fetch() method.
        $options = Core::getOptions( [
            'fields' => '*',
            'params' => [],
            'order' => 'section, name, professor'
        ], $options );
        $courses = $this->model->get( $options );
        return $courses;
    }

    /**
     * @inheritDoc
     */
    public function fetchOne( $options = array() ) {
        // TODO: Implement fetchOne() method.
        $options = Core::getOptions( array(
            'current'=>-1,
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
        else if ( $options['current'] != -1 && $options['table']='terms' ) {
            $options['fields'] = 'term';
            $options['where'] = 'current=?';
            array_push( $options['params'], $options['current'] );
        }else if ( $options['term'] != -1 && $options['table']='terms' ) {
            $options['fields'] = 'term';
            $options['where'] = 'term=?';
            array_push( $options['params'], $options['term'] );
        }

        $courses = $this->model->getOne( $options );
        return $courses;
    }
    public function SendOneTerm( $options = [] ){
        //*****************************************
        //Insert a Term into the terms table
        //*****************************************
        $options = Core::getOptions( array(
            'term'=>-1,
            'startDate'=>-1,
            'endDate'=>-1,
            'current'=>-1,
            'table' => 'terms',
            'fields' => 'term,current,startDate,endDate',
            'params' => array()
        ), $options );

        //term
        if ( $options['term'] != -1 ) {
            array_push( $options['params'], $options['term'] );
        }
        //current
        if ( $options['current'] != -1 && $options['current'] === false  ) {
            array_push( $options['params'], "0" );
        }
        else if ( $options['current'] === true  ) {
            array_push( $options['params'], "1" );
        }
        //dates
        if ( $options['startDate'] != -1 ) {
            array_push( $options['params'], $options['startDate'] );
        }
        if ( $options['endDate'] != -1 ) {
            array_push( $options['params'], $options['endDate'] );
        }
        
        return $this->model->insertOne( $options );
    }
    private function EditTerm( $options = []){
        $options = Core::getOptions( array(
            'current' => -1,
            'term' => -1,
            'table' => 'terms',
            'update' => '',
            'where' => 'term=?',
            'params' => []
        ), $options );

        if($options['term'] != -1){
            $options['update'] = 'current=?';
            array_push( $options['params'], '1' );
            array_push( $options['params'], $options['term'] );
        }
        else if ( $options['current'] != -1) {
            $options['update'] = 'current=?';
            $options['where'] = 'current=?';
            array_push( $options['params'], $options['current'] );
            array_push( $options['params'], '1' );
        }

        $result = $this->model->update( $options );
        return $result;
    }
    public function SendOne( $options = [] ){
        //*****************************************
        //Insert the course into the coursess table
        //*****************************************
        $options = Core::getOptions( array(
            'section'=>-1,
            'name'=>-1,
            'professor'=>-1,
            'term'=>-1,
            'table' => 'courses',
            'fields' => 'section,name,professor,term',
            'params' => array()
        ), $options );

        if ( $options['section'] != -1 ) {
            
            array_push( $options['params'], $options['section'] );
        }if ( $options['name'] != -1 ) {
            
            array_push( $options['params'], $options['name'] );
        }if ( $options['professor'] != -1 ) {
            
            array_push( $options['params'], $options['professor'] );
        }if ( $options['term'] != -1 ) {
            array_push( $options['params'], $options['term'] );
        }

        return $this->model->insertOne( $options );
    }

    /**
     * send all the sections
     * @return string
     */
    public function SendClasses($section,$class,$professor){
        $error="";
        $term=$this->fetchOne(['current'=>1,'table'=>'terms']);
        if($term===false){
            return Ajax::response(['errors'=>"It was not possible to get the current term."], true,"");
        }
        foreach ($section as $key => $item){
            $exist=$this->fetchOne(['section'=>$item,'term'=>$term['term']]);
            if($exist!==false){
                $error.="This class is already in the database <br> section: ".$item." Class name: ".$class[$key].' Professor: '.$professor[$key]."<br>";
            }else{
                $section=$this->SendOne(['section'=>$item,'name'=>$class[$key],'professor'=>$professor[$key],'term'=>$term['term']]);
                if($section===false){
                    $error.="There was an error sending section: ".$item." Class name: ".$class[$key].' Professor: '.$professor[$key]."<br>";
                }
            }
        }

        return Ajax::response(['errors'=>$error], true, "All the data was saved to the server.");
    }

    public function data() {
        if(isset($_POST['section'])&&isset($_POST['class'])&&isset($_POST['professor'])){
            $_POST = Security::sanitize( $_POST );
            $data=$this->SendClasses($_POST['section'],$_POST['class'],$_POST['professor']);
            echo $data;
        }
        else if(isset($_POST['oneSection'])&&isset($_POST['oneName'])&&isset($_POST['oneProfessor'])){
            $_POST = Security::sanitize( $_POST );
            $term=$this->fetchOne(['current'=>1,'table'=>'terms']);
            $temp=$this->SendOne(['section'=>$_POST['oneSection'],'name'=>$_POST['oneName'],'professor'=>$_POST['oneProfessor'],'term'=>$term['term']]);
            if($temp===false){
                $data = Ajax::response([], false, "There was an error sending the data to the database, check if the course already exist.");
            }else{
                $data = Ajax::response([], true, "The course was saved successfully.");
            }
            echo $data;
        }
        else if ( isset($_FILES["file"])) {
            $_POST = Security::sanitize( $_POST );
            // //excel
            // if($_FILES["file"]['type']==="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"){
            //     $data=$this->GetXLSXData();
            // }
            //CSV
            //else 
            if($_FILES["file"]['type']=='application/vnd.ms-excel'){
                $data=$this->GetCSVData();
            }
            else{
                $data = Ajax::response([], false, "There was an issue reading the file please make sure that it is in the correct format.");
            }
            echo $data;
        }
        else if ( isset($_POST["term"])&&isset($_POST["year"])&&isset($_POST["startdate"])&&isset($_POST["enddate"])) {
            $_POST = Security::sanitize( $_POST );
            $current=false;
            $term=$_POST["term"].$_POST["year"];
            if(isset($_POST["current"])){
                $current=true;
                $edit=$this->EditTerm(['current'=>0]);
            }
            $sendterm=$this->SendOneTerm(['term'=>$term,'current'=>$current,'startDate'=>$_POST["startdate"],'endDate'=>$_POST["enddate"]]);
            if($sendterm===false){
                $data = Ajax::response([], false, "There was an issue creating the term.");
            }else{  
                $data = Ajax::response([], true, "The term was created succesfully.");
            }
            
            echo $data;
        }
        else if(isset($_POST["setterm"])&&isset($_POST["setyear"])){
            $setterm=($_POST["setterm"].$_POST["setyear"]);
            $term=$this->fetchOne(['term'=>$setterm,'table'=>'terms']);
            if($term!==false){
                $uncurrent=$this->EditTerm(['current'=>0]);
                if($uncurrent===false){
                    $data = Ajax::response([], false, "There was an issue removing the current term.");
                }else{  
                    $current=$this->EditTerm(['term'=>$setterm]);
                    if($current===false){
                        $data = Ajax::response([], false, "There was an issue setting the term.");
                    }else{  
                        $data = Ajax::response([], true, "The term was set succesfully.");
                    }
                }
            }else{
                $data = Ajax::response([], false, "The term: ".($_POST["setterm"]." ".$_POST["setyear"])." does not exist please create it first");
            }
            echo $data;
        }
        else{
           $this->loadView( "data" );
        }
    }

    /**
     * Gets data from a file .CSV
     * @param $sv array
     * @return 2D array of
     * ['columname1'=>data1,'columname2'=>data2,'columname3'=>data3...]
     */

    public function GetCSVData(){
        $info = ['length'=>0];
        $index =[];
        $row=0;
        if (($handle = fopen($_FILES["file"]['tmp_name'], "r")) !== FALSE) {
            while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
                //"professor"
                //"class"
                //"﻿section" //csv gets weird symbols some times
                //"section"
                //
                if($row!=0){
                    $info[$row-1]=array();
                }
                foreach($data as $col=>$value){
                    if($row==0){
                        array_push( $index, strtolower($value));
                    }else{
                        $info[$row-1][$index[$col]]=$value;
                    }
                }
                $row = $row+1;
            }
            $info['length']=$row-1;
            fclose($handle);
        }
        return Ajax::response(['info' => $info,'index'=>$index], true, "");
    }


    /**
     * Gets data from a file .XLSX
     * @param $sv array
     * @return 2D array of
     * ['columname1'=>data1,'columname2'=>data2,'columname3'=>data3...]
     */
    public function GetXLSXData(){
        $info = ['length'=>0];
        $index =[];
        $file = new SimpleXLSX($_FILES["file"]['tmp_name']);
        if ($file !== FALSE) {
            $data = $file->rows();
            foreach($data as $key=>$item){
                $info['length']=$key;
                if($key!=0){
                    $info[$key-1]=array();
                }
                foreach($item as $col=>$value){
                    if($key==0){
                        array_push( $index, strtolower($value));
                    }else{
                        $info[$key-1][$index[$col]]=$value;
                    }
                }
            }
        }
        return Ajax::response(['info' => $info,'index'=>$index], true, "");
    }

}