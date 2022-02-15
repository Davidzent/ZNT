"use strict";

$(document).ready(function () {
  init();

  function init() {
    var _this = this;

    $('.sortable').sortable();
    $(".sortable").disableSelection();
    $('select.autoload').select2();
    $('header .logout').on('click', function (e) {
      return logoutButtonAction.call(_this, e);
    });
  }

  function logoutButtonAction(e) {
    log(e);
  }
});
/* Creates a Table with filters, pages and limit to the table
id: The table ID
th: The headers for the table
checkbox: if wanted to include checkbox in the table [class,name,valuefromdata]
info: Array holding the [type,class,name,valuefromdata] or [valuefromdata,class] for normal text without being input
data: Data to be put in the table 2D array [index][valuefromdata]
info=[
    0=>['valuefromdata'=>12345,'class'=>('classname1' 'classname2')]    //no type just put it in the table
    1=>['type'=>text,                   'class'=>('classname1' 'classname2') 'name'=>name,'valuefromdata'=>(text)]
    2=>['type'=>date,                   'class'=>('classname1' 'classname2') 'name'=>name,'valuefromdata'=>(normal date no conversion needed)]
    2=>['type'=>datetime-local-convert, 'class'=>('classname1' 'classname2') 'name'=>name,'valuefromdata'=>(date in stamp seconds)]
    3=>['type'=>button,                 'class'=>('classname1' 'classname2') 'name'=>name,'valuefromdata'=>(the button value)]
]
the name is for $_POST
submitvals: array of buttons = {
    type:"type",
    id:"ID"
    value:"value"
}
display: The place to display the table
max: Maximum number of values in table
filters: Number of filters in tables (will be put in filters class div)
Note: the class needs to be the same as the column headert text value for the filters without spaces
*/

function createtable(id, th, checkbox, info, data, submitvals, display, max, filters, extraBtn) {
  var _this2 = this;

  extraBtn = isset(extraBtn) ? extraBtn : false;
  var results = $('.' + display);
  var pageresults = $('.' + display + "pages");
  var options = {
    weekday: 'long',
    year: 'numeric',
    month: 'long',
    day: 'numeric'
  }; //for the date

  results.fadeIn();
  var html = "<table id='" + id + "' class='dataTable'><thead><tr>";
  var currentpage = 0;
  var asc = [];
  var cnt = 0;

  for (var i = 0; i < th.length; i++) {
    if (th[i] == 'Edit' || th[i] == 'Remove' || th[i] == 'Verify' || th[i] == 'Logout') {
      html += '<th>' + th[i] + '<i class="fas fa-sort sort smallest" value="checkbox ' + i + '"></th>';
      cnt++;
    } else if (info[i - cnt][0] == 'date') {
      html += '<th>' + th[i] + '<i class="fas fa-sort sort smallest" value="date ' + i + '"></th>';
    } else {
      html += '<th>' + th[i] + '<i class="fas fa-sort sort smallest" value="text ' + i + '"></th>';
    }

    asc.push(false);
  }

  html += "</tr></thead><tbody>";

  for (var _i = 0; _i < data.length; _i++) {
    if (_i < max || max == -1) {
      html += "<tr>";
    } else {
      html += "<tr style='display: none;'>";
    }

    for (var x = 0; x < checkbox.length; x++) {
      html += "<td class='center'>" + "<input id = '" + _i + "' class='" + checkbox[x][0] + "' name = '" + checkbox[x][1] + "[" + _i + "]' value='" + data[_i][checkbox[x][2]] + "' type='checkbox' /></td>";
    }

    for (var j = 0; j < info.length; j++) {
      if (info[j][0] == 'text') {
        html += "<td class='vcenter'>" + "<input class='" + info[j][1] + _i + "' name = '" + info[j][2] + "[" + _i + "]' value='" + data[_i][info[j][3]] + "' type='hidden' />" + "<p class = '" + info[j][1] + _i + "'>" + data[_i][info[j][3]] + "</p></td>" + "</td>";
      } else if (info[j][0] == 'datetime-local-convert') {
        var time = new Date(data[_i][info[j][3]]);
        time = time.toLocaleString('en-US'); //time.toLocaleDateString("en-US",options)+" "+time.toLocaleTimeString('en-US');

        if (time.includes("Invalid Date")) {
          time = "No Logout";
        }

        html += "<td class = 'wide vcenter'>" + "<input class='" + info[j][1] + _i + "' name = '" + info[j][2] + "[" + _i + "]' value='" + data[_i][info[j][3]] + "' type='hidden' />" + "<p class = '" + info[j][1] + _i + "'>" + time + "</p></td>";
      } else if (info[j][0] == 'date') {
        html += "<td class = 'wide vcenter'>" + "<input class='" + info[j][1] + _i + "' name = '" + info[j][2] + "[" + _i + "]' value='" + data[_i][info[j][3]] + "' type='hidden' />" + "<p class = '" + info[j][1] + _i + "'>" + data[_i][info[j][3]] + "</p></td>";
      } else if (info[j][0] == 'button') {
        html += "<td class = 'wide vcenter'>" + "<input class='" + info[j][1] + "' name = '" + info[j][2] + "[" + _i + "]' value='" + info[j][3] + "' type='button' /></td>";
      } else {
        html += "<td class='vcenter " + info[j][1] + "'>" + data[_i][info[j][0]] + "</td>";
      } //"section"

    }

    html += "</tr>";
  }

  if (submitvals !== false) {
    html += '</tbody><tfoot><tr><td colspan="' + th.length + '">'; //new feature for multiple buttons in the footer.

    for (var _i2 = 0; _i2 < submitvals.length; _i2++) {
      html += '<input id="' + submitvals[_i2].id + '" type = "' + submitvals[_i2].type + '" value = "' + submitvals[_i2].value + '"/>';
    }

    html += '</td></tr></tfoot></table>';
  }

  results.html(html); //filters

  addfilter(id, "", filters);
  $(".filter").on('keyup', function (e) {
    return updatetable.call(_this2, e);
  });
  $(".filtertag").on('change', function (e) {
    return updatetable.call(_this2, e);
  });
  $(".sort").on('click', function (e) {
    return sort.call(_this2, e);
  }); //sort

  function sort(e) {
    var table, index, //the position to be sort on
    type, //the type to be sort on (date,checkbox,text/number)
    arrow, th, tr;
    index = $(e.currentTarget).attr('value').split(' '); // index = e.currentTarget.defaultValue.split(' ');

    type = index[0];
    index = parseInt(index[1]);
    table = document.getElementById(id); //the type of sort decending(smallest) or ascending (biggest)

    th = table.rows[0].getElementsByTagName("TH")[index];
    arrow = th.childNodes[1];
    tr = table.rows; //This shit took me almost an hour
    //get the cell value function

    var getCellValue = function getCellValue(tr, index) {
      return tr.children[index].innerText || tr.children[index].textContent || tr.children[index].childNodes[0].checked;
    }; //simple swap arrow function


    var jArrow = $(arrow); //change all current up and downs to neutrual

    $('.sort.fa-sort-up').removeClass('fa-sort-up').addClass('fa-sort');
    $('.sort.fa-sort-down').removeClass('fa-sort-down').addClass('fa-sort');

    var swaparrow = function swaparrow(asc) {
      return asc ? $(arrow).attr('class', 'fas fa-sort-up sort biggest boldup') : $(arrow).attr('class', 'fas fa-sort-down sort smallest bolddown');
    }; // unbold one if it is not the same index as the one clicked


    var bold = function bold(arrow, indx) {
      return index != indx ? arrow.className = arrow.className.replace(/smallest bolddown|biggest boldup/gi, "smallest") : asc;
    }; // unbold all


    Array.from(table.rows[0].getElementsByTagName("TH")).forEach(function (arrow, index) {
      return bold(arrow.childNodes[1], index);
    }); //compares two values
    //if they are number just check whichone is greater by subtracting v1 and v2 (v1 is smaller when the result is negative)
    //else just use localecompare to check if it is a string
    //for now I don't want to check for dates but I believe the localeCompare deals with that (I hope)

    var comparer = function comparer(index, asc) {
      return function (a, b) {
        return function (v1, v2) {
          return v1 !== '' && v2 !== '' && !isNaN(v1) && !isNaN(v2) ? v1 - v2 : v1.toString().localeCompare(v2);
        }(getCellValue(asc ? a : b, index), getCellValue(asc ? b : a, index), swaparrow(asc));
      };
    }; //do the work...


    Array.from(table.tBodies[0].querySelectorAll('tr')) //get all the tr from the first table tbody so that it does not get the theader and tfoot ones
    //sort function from Array
    .sort(comparer(index, asc[index] = !asc[index])) //swap from asc to desc everytime it is click
    .forEach(function (rows) {
      return table.tBodies[0].appendChild(rows);
    }); //insert into the tbody the new organized values
    //update the table to prevent erros from pages

    updatetable(false);
  } //pages


  if (max != -1) {
    var npages = data.length / max;
    html = "<input class='newpage' type='button' value='..' style='display: none;'>";

    for (var _i3 = 0; _i3 < npages && _i3 <= 10; _i3++) {
      if (_i3 == 10) {
        html += "<input class='newpage' type='button' value='...' >";
      } else {
        html += "<input class='newpage' type='button' value='" + (_i3 + 1) + "' >";
      }
    }

    pageresults.html(html);
    $(".newpage").on('click', function (e) {
      return updatetable(e);
    });
  } //general updatetable


  function updatetable(e) {
    var updatepages = false;

    if (e.type == 'click') {
      currentpage = e.currentTarget.defaultValue;

      if (currentpage == '..' || currentpage == '...') {
        updatepages = true;
        page = $('.newpage');
        newpages = currentpage == '..' ? -10 : 10;

        for (var _i4 = 1; _i4 < page.length - 1; _i4++) {
          page[_i4].value = parseInt(page[_i4].value) + newpages;
        }

        page[0].style.display = '';
        currentpage = parseInt(page[1].value);
      }

      currentpage--;
    } else {
      //this fixes a bug that the pages have when you input a value in the filters and not in the first page
      updatepages = true;
      page = $('.newpage');

      for (var _i5 = 1; _i5 < page.length - 1; _i5++) {
        page[_i5].value = _i5;
      }

      page[0].style.display = '';
      currentpage = 0;
    } //the table


    var table = document.getElementById(id); //temporal variables

    var temp = document.getElementsByClassName("filtertag");
    var temp2 = document.getElementsByClassName("filter");
    var index = []; //the colums to search on

    var keywords = []; //the values to be filter on

    var x = 0; //counter for the maximum values in page & the number of matches with the filter

    var check = false; //used later to check if the keywords matches the filters

    var inf = []; //holds the position to be filter from the info array

    var tr; //tr from table

    var td; //td from table

    var startat = currentpage * (max == -1 ? 0 : max); //value to start filtering from (used for pages)
    //get all the th text into an array

    var cols = th.map(function (s) {
      return s.toUpperCase().replace(/\s/g, '');
    }); //get the info

    for (var k = 0; k < temp.length; k++) {
      inf[k] = info[temp[k].value][1].split(' ');

      for (var _i6 = 0; _i6 < inf[k].length; _i6++) {
        index[k] = cols.indexOf(inf[k][_i6].toUpperCase());
        if (index[k] != -1) break;
      }

      keywords[k] = temp2[k].value.toUpperCase();
    }

    tr = table.getElementsByTagName("tr");

    if (index != null) {
      for (var _i7 = 1; _i7 < tr.length - 1; _i7++) {
        check = true;

        for (var _k = 0; _k < filters; _k++) {
          td = tr[_i7].getElementsByTagName("td")[index[_k]];

          if (td) {
            txtValue = td.textContent || td.innerText;
            if (txtValue.toUpperCase().indexOf(keywords[_k]) == -1) check = false;
          } else {
            check = false;
          }
        }

        if (_i7 < startat + 1 || x >= max && max != -1) {
          //if before or after the start of the page
          tr[_i7].style.display = "none";

          if (check && x >= max && max != -1) {
            x++;
          }
        } else {
          if (check) {
            tr[_i7].style.display = "";

            if (x % 2 == 1) {
              tr[_i7].style.backgroundColor = "#cacaca";
              x++;
            } else {
              tr[_i7].style.backgroundColor = "white";
              x++;
            }
          } else {
            tr[_i7].style.display = "none";
          }
        }
      }

      if ((updatepages || e.type != 'click') && max != -1) {
        page = $('.newpage');
        newpages = x / max + 1;

        for (var _i8 = 0; _i8 < page.length; _i8++) {
          if (_i8 <= newpages && _i8 <= 11) {
            page[_i8].style.display = "";
          } else {
            page[_i8].style.display = "none";
          }
        }

        if (startat == 0) {
          page[0].style.display = "none";
        } else {
          page[0].style.display = "";
        }
      }
    }
  }
} //adds a filter for a table to the html
//first <tr> needs to have <th> not <td>


function addfilter(tableid, defaultfilter, filters) {
  var toaddfilter = $('.filters');
  toaddfilter.html("");

  for (var j = 0; j < filters; j++) {
    var html = "<select class='filtertag " + j + "'>"; //get all the th text into an array

    var cols = $('#' + tableid + ' tr th').toArray().map(function (s) {
      return s.innerText.trim();
    }); //remove the edit and remove column

    cols = cols.filter(function (s) {
      return s !== 'Edit' && s !== 'Remove' && s !== 'Logout' && s !== 'Verify';
    });
    var temp = 0;

    for (var i = 0; i < cols.length; i++) {
      temp = cols[i];

      if (defaultfilter == "" && i == j) {
        html += "<option selected='selected' value=" + i + ">" + temp + "</option>";
      } else if (defaultfilter == temp) {
        html += "<option selected='selected' value=" + i + ">" + temp + "</option>";
      } else {
        html += "<option value=" + i + ">" + temp + "</option>";
      }
    }

    html += "</select>";
    html += "<input type='text' class='filter " + j + "' placeholder='1234567' title='Select the filter and input the value.'/>";

    if (j % 4 == 0 && j != 0) {
      toaddfilter.append(html + "<br>");
    } else {
      toaddfilter.append(html);
    }
  }
} //checkboxmains: the name of the checkbox to press to hide/show <p> and input text/hidden
//checkboxothers: other checkboxes if onlyonecheckbox is enable else leave it empty
//pclass: the classes of the <p> tags
//type: the new type of the input
//Note: <p> tag and <input> tags need to have the same class name followed by the id : classid (nospaces)


function ptoanyinput(checkboxmains, checkboxothers, pclass, type) {
  for (var i = 0; i < checkboxmains.length; i++) {
    $('.' + checkboxmains[i]).on('click', function () {
      var $box = $(this);

      if ($box.is(":checked")) {
        for (var j = 0; j < pclass.length; j++) {
          //select the hidden input with the class="class+id"
          var inputs = $("input:hidden[class='" + pclass[j] + $box.attr("id") + "']");
          var p = $("p[class='" + pclass[j] + $box.attr("id") + "']");
          p.hide();

          for (var _i9 = 0; _i9 < inputs.length; _i9++) {
            inputs[_i9].type = type;
          }
        }
      } else {
        for (var _j = 0; _j < pclass.length; _j++) {
          //querySelectorAll rather than $() because for some reason it does not work with that one
          var _inputs = document.querySelectorAll('input[type="' + type + '"][class="' + pclass[_j] + $box.attr("id") + '"]'); //select the p tags


          var _p = $("p[class='" + pclass[_j] + $box.attr("id") + "']");

          _p.show();

          for (var _i10 = 0; _i10 < _inputs.length; _i10++) {
            _inputs[_i10].type = "hidden";
          }
        }
      }
    });
  } //when other checkbox is click


  for (var _i11 = 0; _i11 < checkboxothers.length; _i11++) {
    $('.' + checkboxothers[_i11]).on('click', function () {
      var $box = $(this);

      if ($box.is(":checked")) {
        for (var j = 0; j < pclass.length; j++) {
          //querySelectorAll rather than $() because for some reason it does not work with that one
          var inputs = document.querySelectorAll('input[type="' + type + '"][class="' + pclass[j] + $box.attr("id") + '"]'); //select the p tags

          var p = $("p[class='" + pclass[j] + $box.attr("id") + "']");
          p.show();

          for (var _i12 = 0; _i12 < inputs.length; _i12++) {
            inputs[_i12].type = "hidden";
          }
        }
      }
    });
  }
}

function onlyonecheckbox() {
  //Only one checkbox is possible at a time
  $("input:checkbox").on('click', function () {
    var $box = $(this);

    if ($box.is(":checked")) {
      var group = "input:checkbox[value='" + $box.attr("value") + "']";
      $(group).prop("checked", false);
      $box.prop("checked", true);
    } else {
      $box.prop("checked", false);
    }
  });
}