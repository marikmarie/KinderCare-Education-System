<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use App\Models\AssignmentModel;
use App\Models\PupilModel;
use App\Models\MarksModel;
use App\Models\CommentModel;

class MarksController extends Controller
{
    private function grading($data, $attempted){
        $passMark =  70;
        $pupil_b = 0;
        $pupil_a = 0;
        
        foreach($data as $key=>$value){
            if($value->marks >=70){
                $pupil_a ++;
            }
            else{
                $pupil_b++;
            }
            
        }
        if($attempted==0){
            $passed_per =0;
         $failed_per = 0;

        }
        else{
            $passed_per = ($pupil_a/$attempted)*100;
            $failed_per = ($pupil_b/$attempted)*100;
   
        }
         

        return array($pupil_a, $pupil_b, $passed_per,$failed_per);
        
    }

    private function check_comment($id){
          if(CommentModel::where('assignment_id', '=', $id)->count()){
                 $comment = CommentModel::where('assignment_id', '=', $id)->pluck('comment')[0];
                 return $comment;
          }
          else{
              return NULL;;
          }
    }

    public function  index(){
        
        //check if teacher has an assignment
       if(AssignmentModel::where('teacher_id', Auth::user()->id)->count()> 0){
        $id = AssignmentModel::where('teacher_id', Auth::user()->id)->pluck("id")[0];
        
        //total pupils who attempted
        $total_pupils_a = MarksModel::where('assignment_id', $id)->count();
        $total_pupils = PupilModel::all()->count();

        $data = MarksModel::join('pupil', 'pupil.id', '=', 'marks.pupil_id')
              		->where('marks.assignment_id', '=', $id)
              		->get();
         $grading =$this->grading($data, $total_pupils_a);
         $getcomment = $this->check_comment($id);
         
         
    

        return view('reports.index',compact('total_pupils_a', 'total_pupils', 'data','grading', 'getcomment' ) );


    }
    else{
         return  view('reports.noassignment');
    }

    }
    public function attemptsSummary(){

        
            //check if teacher has an assignment
           if(AssignmentModel::where('teacher_id', Auth::user()->id)->count()> 0){
            $ids = AssignmentModel::where('teacher_id', Auth::user()->id)->pluck("id");
            $totalAttempts = 0;
            $totalMissed = 0;
            $passed = 0;
            $failed = 0;
            $totalPupils = PupilModel::all()->count();
            $assignments = [];
            //total pupils who attempted
            $total_pupils = PupilModel::all()->count();
            $passMark = 70;
            foreach($ids as $id){
                $totalAttempts = MarksModel::where('assignment_id', $id)->count();
                $passed = MarksModel::where('assignment_id', $id)->where('marks','>=',$passMark)->count();
                $failed = MarksModel::where('assignment_id', $id)->where('marks','<',$passMark)->count();
             
                // $data = MarksModel::join('pupil', 'pupil.id', '=', 'marks.pupil_id')
                // ->where('marks.assignment_id', '=', $id)
                // ->get();
                // $grading =$this->grading($data, $total_pupils_a);
                // $getcomment = $this->check_comment($id);
                $percentP = $totalAttempts==0?0:($passed==0?0:$passed/$totalAttempts*100);
                $percentF = $totalAttempts==0?0:($failed==0?0:$failed/$totalAttempts*100);
                $assignments[] = array(
                    'id'=>$id,
                    'totalAttempts'=>$totalAttempts,
                    'name'=>AssignmentModel::where('id',$id)->pluck('name')[0],
                    'passed'=>$passed,
                    'failed'=>$failed,
                    '%passed'=>$percentP,
                    '%failed'=>$percentF,
                    'comment'=>AssignmentModel::where('id',$id)->pluck('comment')[0]
                    

                );
  
            }
             
             
        
    
            return view('reports.attempts',compact('assignments'));

    
    
        }
        else{
             return  view('reports.noassignment');
        }
    
        }
        public function assignmentSummary($id){
           
            if(AssignmentModel::where('teacher_id', Auth::user()->id)->count()> 0){
                $assignmentName = AssignmentModel::where('id',$id)->pluck('name')[0];
                $totalAttempts = MarksModel::where('assignment_id', $id)->count();
                // $passed = MarksModel::where('assignment_id', $id)->where('marks','>=',$passMark)->count();
                // $failed = MarksModel::where('assignment_id', $id)->where('marks','<',$passMark)->count();
                $pupils = MarksModel::join('pupil', 'pupil.id', '=', 'marks.pupil_id')
                    ->where('marks.assignment_id', '=', $id)
                    ->get();
                //   dd($pupils);

                // $data = MarksModel::join('pupil', 'pupil.id', '=', 'marks.pupil_id')
                // ->where('marks.assignment_id', '=', $id)
                // ->get();
                // $grading =$this->grading($data, $total_pupils_a);
                // $getcomment = $this->check_comment($id);

                return view('reports.attemptSummary',compact('pupils','assignmentName'));
    
                
            }
                 
            else{
                 return  view('reports.noassignment');
            }
             
        }
        public function addComment($assignmentId){
            $assignment = AssignmentModel::find($assignmentId);
            return view('reports.addComment',compact('assignment'));
        }
        public function comment(Request $request){
            $assignmentId = $request->assignmentId;
            $comment = $request->comment;
            
            AssignmentModel::find($assignmentId)->update(['comment'=>$comment]);
            return redirect()->route('reports.attempts')
            ->with('success', 'Pupil Status Updated successfully');
        }
        public function addPupilComment($assignmentId,$pupilId){
            $pupil = PupilModel::find($pupilId);
            $assignment = AssignmentModel::find($assignmentId);
            return view('reports.addCommentToPupil',compact('pupil','assignment'));
        }
        public function commentPupil(Request $request){
            $assignmentId = $request->assignmentId;
            $comment = $request->comment;
            $pupilId = $request->pupilId;
            
            MarksModel::where(['pupil_id'=>$pupilId,'assignment_id'=>$assignmentId])->update(['comment'=>$comment]);
            return redirect()->route('reports.assignmentAttemptsSummary',['id'=>$assignmentId]);
            
        }
    
}
