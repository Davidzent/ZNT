<?php

class courses extends module {
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
            'table' => 'courses',
            'fields' => '*',
            'where' => '',
            'params' => array()
        ), $options );

        if ( $options['section'] != -1 ) {
            $options['where'] = 'section=?';
            array_push( $options['params'], $options['section'] );
        }

        $courses = $this->model->getOne( $options );
        return $courses;
    }
    public function SendOne( $options = [] ){
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

    /**
     * send all the sections
     * @return string
     */
    public function SendClasses($section,$class,$professor){
        $error="";
        foreach ($section as $key => $item){
            $exist=$this->fetchOne(['section'=>$item]);
            if($exist!==false){
                $error.="This class is already in the database <br> section: ".$item." Class name: ".$class[$key].' Professor: '.$professor[$key]."<br>";
            }else{
                $section=$this->SendOne(['section'=>$item,'name'=>$class[$key],'professor'=>$professor[$key]]);
                if($section===false){
                    $error.="There was an error sending section: ".$item." Class name: ".$class[$key].' Professor: '.$professor[$key]."<br>";
                }
            }
        }

        return Ajax::response(['errors'=>$error], true, "All the data was send to the server.");
    }

    public function create() {
        if(isset($_POST['section'])&&isset($_POST['class'])&&isset($_POST['professor'])){
            $_POST = Security::sanitize( $_POST );
            $data=$this->SendClasses($_POST['section'],$_POST['class'],$_POST['professor']);
            echo $data;
        }
        else if(isset($_POST['oneSection'])&&isset($_POST['oneName'])&&isset($_POST['oneProfessor'])){
            $_POST = Security::sanitize( $_POST );
            $temp=$this->SendOne(['section'=>$_POST['oneSection'],'name'=>$_POST['oneName'],'professor'=>$_POST['oneProfessor']]);
            if($temp===false){
                $data = Ajax::response([], false, "There was an error sending the data to the database, check if the course already exist.");
            }else{
                $data = Ajax::response([], true, "The course was send succesfully.");
            }
            echo $data;
        }
        else if ( isset($_FILES["file"])) {
            $_POST = Security::sanitize( $_POST );
            //excel
            if($_FILES["file"]['type']==="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"){
                $data=$this->GetXLSXData();
            }
            //CSV
            else if($_FILES["file"]['type']=='application/vnd.ms-excel'){
                $data=$this->GetCSVData();
            }
            else{
                $data = Ajax::response([], false, "There was an issue reading the file please make sure that it is in the correct format.");
            }
            echo $data;
        }
        else{
           $this->loadView( "create" );
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