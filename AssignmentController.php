<?php

namespace App\Http\Controllers;

use App\Models\AssignmentModel;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class AssignmentController extends Controller
{
    //
    public function index()
    {
        // $data = AssignmentModel::all()->toArray();
        // //dd($data[0]);
        // $newData = array();
        // foreach($data as $key=>$value){
        //     //dd($key);
        //     //array_push("")
        //     Carbon::
        // }
        $data = AssignmentModel::all();

        return view("assignment.index", compact("data"));
    }

    public function create(){
        

        return view('assignment.create');
    }

    public function store(Request $request){
        $this->validate($request, [
            'name'=>'required',
            'dateOfAttempt'=>'required',
            'startTime'=>'required',
            'characters'=>'required|min:1|max:8',
            'endTime'=>'required'
        ]);

        //dd($request->name);
        $insert = AssignmentModel::create([
            "url"=>$request->characters,
            'startTime'=>$request->startTime,
            'endTime'=>$request->endTime,
            "dateOfAttempt"=>$request->dateOfAttempt,
            "assignmentDue"=>false,
            "name"=>$request->name,
            "teacher_id"=>Auth::user()->id
        ]);

        //dd($insert);
        return redirect()->route('assignment.index')
        ->with('success', 'Assignment  Added successfully');

    }
}
