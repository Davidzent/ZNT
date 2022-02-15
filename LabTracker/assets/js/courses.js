$(document).ready(function () {
    if ( $( '#coursesCreate' ).length > 0 ) {
        CourseInit();
    }
    function CourseInit(){
        // $('#ClassAction').submit(function (e) {
        //     submitfile.call(this, e);
        // });
        $('#CreateOne').on('click', (e) => CreateOneprompt.call(this, e));
        $('#Create').on('click', (e) => Createprompt.call(this, e));


        //Modal To Create a New Course
        function CreateOneprompt(e) {
            let results = $('.results');
            var html = '<label for="oneSection"><b>Section</b></label>' +
                '<input type="text" placeholder="12345" name="oneSection" >' +
                '<label for="oneName"><b>Class Name</b></label>' +
                '<input type="text" placeholder="CIS 5" name="oneName" >' +
                '<label for="oneProfessor"><b>Professor</b></label>' +
                '<input type="text" placeholder="Enter Professor Name" name="oneProfessor" >' +
                '<div class="errors"></div>' +
                '<input id="CreateOneCourse" type="submit" value="Create"/>';
            results.html(html);
            results=$('.adminphase2');
            results.html("");
            results=$('.adminphase2pages');
            results.html("");
            results=$('.filters');
            results.html("");
            $('#CreateOneCourse').on('click', function (e) {
                CreateOneCourse.call(this, e);
            });
        }
        function CreateOneCourse(e){
            e.preventDefault();
            let form = $('#ClassAction');
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
                            messageModal(d.data.msg,"Register",false,"",true);
                        } else {
                            error.append("<p>" + d.data.error + "</p>");
                            error.slideDown(250);
                        }
                    }
                });

            }

        }
        function Createprompt(e){
            let results = $('.results');
            html='<p>Enter a .csv <a href="https://drive.google.com/file/d/1plKnd1YyTAYtuvcvWWhIv-PnRgV_MTCk/view?usp=sharing">file as</a> <br>Sections&emsp;Class &ensp;Professor<br>12345 &ensp;CSC 5 &emsp;John Doe</p>'+
            '<input type="file" id="filecheck" name="file" accept="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"/>';
            results.html(html);
            $('#filecheck').on('change', (e) =>  CreateCourse.call(this, e));
        }

        function CreateCourse(e){
            var form = $('#ClassAction');
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
                        id: 'CreateFromtable',
                        value: "Upload to Database"
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
                        messageModal(d.data.error,"Upload to Database",false,"",true);
                    }
                }
            });
        }
        function submitfile(e){
            e.preventDefault();
            //Function Variables
            let form = $('#ClassAction');
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
                            messageModal(d.data.errors,"Error Uploading To The Database",false,"",true);
                        }else{
                            messageModal(d.data.msg,"Upload to Database",false,"",true);
                        }

                    } else {
                        error.append("<p>" + d.data.error + "</p>");
                        error.slideDown(250);
                    }
                }
            });
        }
    }
});
