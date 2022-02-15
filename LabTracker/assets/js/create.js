/**
 * Copyright (C) David Guijosa Infante - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by David Guijosa Infante <davidgin641@gmail.com>, 8/11/21 1:27 PM
 */
$(document).ready(function () {
    if ( $( '#createData' ).length > 0 ) {
        CourseInit();
    }
    function CourseInit(){
        // $('#CreateAction').submit(function (e) {
        //     submitfile.call(this, e);
        // });
        $('#CreateOneCourse').on('click', (e) => CreateOneCprompt.call(this, e));
        $('#CreateCourses').on('click', (e) => Createprompt.call(this, e));
        $('#CreateTerm').on('click', (e) => CreateOneTprompt.call(this, e));
        $('#SetTerm').on('click', (e) => SetTprompt.call(this, e));

        function SetTprompt(){
            let results = $('.results');
            let year = new Date().getFullYear();
            var html = 
                '<select name="setterm" >' +
                '<option value="winter">Winter</option>'+
                '<option value="spring">Spring</option>'+
                '<option value="summer">Summer</option>'+
                '<option value="fall">Fall</option></select>'+
                '<select name="setyear" >' +
                '<option value="'+(year-1)+'">'+(year-1)+'</option>'+
                '<option selected="selected" value="'+(year)+'">'+(year)+'</option>'+
                '<option value="'+(year+1)+'">'+(year+1)+'</option></select>'+
                '<input class="SetTerm" type="submit"/>';
                
            results.html(html);
            results=$('.adminphase2');
            results.html("");
            results=$('.adminphase2pages');
            results.html("");
            results=$('.filters');
            results.html("");
            $('.SetTerm').on('click', function (e) {
                SetTerm.call(this, e);
            });
        }
        function SetTerm(e){
            e.preventDefault();
            let form = $('#CreateAction');
            let data = $(form).serializeArray();
            let map = {};
            //get data
            jQuery.each(data, function (i, field) {
                map[field.name] = field.value;
            }); //get form data for verify
            $.ajax({
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $(form).attr('action'),
                data: map, //form data
                success: (d) => {
                    if (d.success) {
                        messageModal(d.data.msg,"Current Term",false,"",true);
                    } else {
                        messageModal(d.data.error,"Current Term Error",false,"",true);
                    }
                }
            });
        }
        //Modal To Create a New Term
        function CreateOneTprompt(e) {
            let results = $('.results');
            let year = new Date().getFullYear();
            var html = 
                '<select name="term" >' +
                '<option value="winter">Winter</option>'+
                '<option value="spring">Spring</option>'+
                '<option value="summer">Summer</option>'+
                '<option value="fall">Fall</option></select>'+
                '<select name="year" >' +
                '<option value="'+(year-1)+'">'+(year-1)+'</option>'+
                '<option selected="selected" value="'+(year)+'">'+(year)+'</option>'+
                '<option value="'+(year+1)+'">'+(year+1)+'</option></select><br>'+
                'Start: <input type="date" name="startdate" >' +
                'End: <input type="date" name="enddate" >' +
                '<input type="checkbox" name="current" >Current Term?<br>' +
                '<input class="CreateOneTerm" type="submit" value="Create"/>';
                
            results.html(html);
            results=$('.adminphase2');
            results.html("");
            results=$('.adminphase2pages');
            results.html("");
            results=$('.filters');
            results.html("");
            $('.CreateOneTerm').on('click', function (e) {
                CreateOneTerm.call(this, e);
            });
        }

        //Modal To Create a New Course
        function CreateOneCprompt(e) {
            let results = $('.results');
            var html = '<label for="oneSection"><b>Section</b></label>' +
                '<input type="text" placeholder="12345" name="oneSection" >' +
                '<label for="oneName"><b>Class Name</b></label>' +
                '<input type="text" placeholder="CIS 5" name="oneName" >' +
                '<label for="oneProfessor"><b>Professor</b></label>' +
                '<input type="text" placeholder="Enter Professor Name" name="oneProfessor" >' +
                '<div class="errors"></div>' +
                '<input class="CreateOneCourse" type="submit" value="Create"/>';
            results.html(html);
            results=$('.adminphase2');
            results.html("");
            results=$('.adminphase2pages');
            results.html("");
            results=$('.filters');
            results.html("");
            $('.CreateOneCourse').on('click', function (e) {
                CreateOneCourse.call(this, e);
            });
        }
        function CreateOneTerm(e){
            e.preventDefault();
            let form = $('#CreateAction');
            let error = $('.errors', form);
            let data = $(form).serializeArray();
            let map = {};
            //get data
            jQuery.each(data, function (i, field) {
                map[field.name] = field.value;
            }); //get form data for verify
            $.ajax({
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $(form).attr('action'),
                data: map, //form data
                success: (d) => {
                    if (d.success) {
                        messageModal(d.data.msg,"Create One Term",false,"",true);
                    } else {
                        messageModal(d.data.error,"Create One Term Error",false,"",true);
                    }
                }
            });
        }
        function CreateOneCourse(e){
            e.preventDefault();
            let form = $('#CreateAction');
            let error = $('.errors', form);
            let errors = [];
            let data = $(form).serializeArray();
            let map = {};
            //get data
            jQuery.each(data, function (i, field) {
                map[field.name] = field.value;
            }); //get form data for verify
            errors = verifyForm(form, {
                oneProfessor: {
                    regex: regex['name'],
                    msg: "Must be a real name"
                },
                oneSection: {
                    regex: regex['section'],
                    msg: "Must be a course section using only 5 numbers"
                }
            });
            if (errors) {
                displayErrors( form, error, errors );
                error.slideDown();
            } else {
                displayErrors( form, error, errors );
                $.ajax({
                    type: 'POST',
                    dataType: 'json',
                    url: CORE_URL + $(form).attr('action'),
                    data: map, //form data
                    success: (d) => {
                        if (d.success) {
                            messageModal(d.data.msg,"Create One Course",false,"",true);
                        } else {
                            messageModal(d.data.error,"Create One Course Error",false,"",true);
                        }
                    }
                });

            }
        }
        function Createprompt(e){
            let results = $('.results');
            html='<p>Enter a .csv <a href="https://drive.google.com/file/d/1plKnd1YyTAYtuvcvWWhIv-PnRgV_MTCk/view?usp=sharing">file as</a> <br>Section&emsp;Class &ensp;Professor<br>12345 &ensp;CSC 5 &emsp;John Doe</p>'+
            '<input type="file" id="filecheck" name="file" accept="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"/>';
            results.html(html);
            $('#filecheck').on('change', (e) =>  CreateCourse.call(this, e));
        }

        function CreateCourse(e){
            var form = $('#CreateAction');
            var formData = new FormData(form[0]);
            $.ajax({
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $(form).attr('action'),
                data: formData, //form data
                contentType: false,
                processData: false,
                success: (d) => {
                    //Table options
                    let th=['Edit','Section','Class Name','Professor'];
                    let index=d.data.index;
                    let checkbox=[
                        ['edit','section',index[0]]
                    ];
                    let info=[
                        ['text','section','section',index[0]],
                        ['text','classname','class',index[1]],
                        ['text','professor','professor',index[2]],
                    ];
                    let submitvals={
                        length:1,
                        0:{
                            id: 'CreateFromtable',
                            value: "Upload to Database",
                            type: 'submit'
                        }
                    };
                    let display='adminphase2';
                    max=50;
                    filters=3;
                    if (d.success) {
                        results=$('.'+display);
                        results.fadeIn();
                        createtable('FileTable',th,checkbox,info,d.data.info,submitvals,display,max,filters);
                        let checkboxmains = ["edit"];
                        let checkboxothers = [];
                        let pclass = ["section","classname",'professor'];
                        //Only one checkbox is possible at a time
                        onlyonecheckbox();
                        ptoanyinput(checkboxmains,checkboxothers,pclass,"text");

                        $('#CreateFromtable').on('click',function (e) {
                            submitfile.call(this, e);
                        });
                    } else {
                        messageModal(d.data.error,"Error Loading Courses From File",false,"",true);
                    }
                }
            });
        }
        function submitfile(e){
            e.preventDefault();
            //Function Variables
            let form = $('#CreateAction');
            let error = $('.errors', form);
            let data = $(form).serializeArray();
            let map = {};
            //get data
            jQuery.each(data, function (i, field) {
                map[field.name] = field.value;
            }); //get form data for verify

            $.ajax( {
                type: 'POST',
                url: CORE_URL + $( form ).attr( 'action' ),
                dataType: 'json',
                data: map,
                success: function ( d ) {
                    if (d.success) {
                        if(d.data.errors){
                            messageModal(d.data.errors,"Error Uploading Courses To The Database",false,"",true);
                        }else{
                            messageModal(d.data.msg,"Upload Courses to Database",false,"",true);
                        }

                    } else {
                        messageModal(d.data.error,"Error Uploading Courses To The Database",false,"",true);
                    }
                }
            });
        }
    }
});