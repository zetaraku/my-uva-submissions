#!/usr/bin/perl
use strict;

my $numberOfCases=<STDIN>;
for my $k(0..$numberOfCases-1){
	my $result=&find_solution;
	if(defined $result){
		printf "Departure %04d %s\n", $result->[0], $result->[2];
		printf "Arrival   %04d %s\n", $result->[1], $result->[3];
	}else{
		printf "No connection\n";
	}
}
<STDIN>;

sub find_solution{
	my %citiesToNums;
	my $numberOfCities=<STDIN>;
	for my $i(0..$numberOfCities-1){
		chomp(my $tmp=<STDIN>);
		$citiesToNums{$tmp}=$i;
	}

	my @timetable;
	my @lastStopCity;
	my @stopTrainsOfCity;

	my $numberOfTrains=<STDIN>;
	for my $trainnum(0..$numberOfTrains-1){
		my $numberOfStops=<STDIN>;
		my $lastcitynum;
		for my $j(0..$numberOfStops-1){
			my($timestr, $cityname)=split /\s+/, <STDIN>;
			my $citynum=$citiesToNums{$cityname};
			$timetable[$trainnum][$citynum]=$timestr;			#record time table
			push @{$stopTrainsOfCity[$citynum]}, $trainnum;		#add the train to the list of the city
			$lastStopCity[$trainnum][$citynum]=$lastcitynum if(defined $lastcitynum);#record the back stop
			$lastcitynum=$citynum;
		}
	}

	my($starttime,$startpoint,$endpoint);
	$starttime=<STDIN>;chomp($startpoint=<STDIN>);chomp($endpoint=<STDIN>);
	my $startno=$citiesToNums{$startpoint};
	my $endno=$citiesToNums{$endpoint};

	my %terminalTrainsOfTimes;
	defined $timetable[$_][$endno] and push @{$terminalTrainsOfTimes{$timetable[$_][$endno]}}, $_
		for(0..$numberOfTrains-1);

	my @achieved;
	my @toProcess;				#list of <train number, city number>
	my %foundBeginTime;			#list ordered

	for my $terminalTime(sort {$a<=>$b} keys %terminalTrainsOfTimes){	#process every pair <arrive time, train list> (in order from earlier to latter arrive time)
		my $trainsReachTerminal=$terminalTrainsOfTimes{$terminalTime};
		push @toProcess, [$_,$endno] for(@$trainsReachTerminal);		#push every <trains, terminal> of this arrive time into process list
		while(@toProcess){												#while process list is not empty
			my($t,$c)=@{pop @toProcess};								#<train number, city number> = pop process list
			$achieved[$t][$c]=1;										#set this achieved=true to prevent revisiting
			if($c==$startno){																#if beginning reached
				$foundBeginTime{$timetable[$t][$c]}=1 if($timetable[$t][$c]>=$starttime);	#if the begin time is valid (after the departing time) then put the begin time into find list
			}else{
				push @toProcess, [$t,$lastStopCity[$t][$c]]		#add the previous stop to process list (if exists and not achieved)
					if(defined $lastStopCity[$t][$c] && !$achieved[$t][$lastStopCity[$t][$c]]);
				!$achieved[$_][$c] && $timetable[$_][$c]<=$timetable[$t][$c] and push @toProcess, [$_,$c]								#add every transferable stop to process list (if not achieved and time<=now)
					for(@{$stopTrainsOfCity[$c]});
			}
			return [(sort {$b<=>$a} keys %foundBeginTime)[0],$terminalTime,$startpoint,$endpoint] if(%foundBeginTime);#if any valid beginning reached, take the latest result
		}
	}
	undef;
}