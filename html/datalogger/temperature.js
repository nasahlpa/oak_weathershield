$(function() {
 
    var x_values = [];
    var y_values = [];
    var switch1 = true;
    var identifier = "temperature";
    $.get('data.php', {identifier: "temperature", time: set_time }, function(data) {
        
        data = data.split('/');
        for (var i in data)
        {
            if (switch1 == true)
            {
                x_values.push(data[i]);
                switch1 = false;
            }
            else
            {
                y_values.push(parseFloat(data[i]));
                switch1 = true;
            }
 
        }
        x_values.pop();
        
        $('#temperature').highcharts({
            chart : {
                type : 'spline'
            },
            title : {
                text : 'Temperature'
            },
            subtitle : {
                text : 'last 24h'
            },
            xAxis : {
                tickInterval:30,
                title : {
                    text : 'Time'
                },
                categories : x_values
            },
            yAxis : {
                min: 0,
                max: 30,
                tickInterval:5,
                title : {
                    text : 'Temperature'
                },
                labels : {
                    formatter : function() {
                        return this.value + "° C"
                    }
                }
            },
            exporting: { enabled: false },
            tooltip : {
                crosshairs : true,
                shared : true,
                valueSuffix : ''
            },
            plotOptions : {
                spline : {
                    marker : {
                        radius : 4,
                        lineColor : '#666666',
                        lineWidth : 1
                    }
                }
            },
            series : [{
                showInLegend: false,
                name : 'Temperature',
                data : y_values
            }]
        });
    });
});
