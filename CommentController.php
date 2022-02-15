<?php

namespace App\Http\Controllers;


use App\Models\AssignmentModel;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use App\Models\CommentModel;




class CommentController extends Controller
{
    //
    public function create()
    {
        return view("comment.create");
    }

    //store comment
    public function store(Request $request)
    {
        $this->validate($request, [
            'comment'=>'required'
        ]);
       $id = AssignmentModel::where('teacher_id', Auth::user()->id)->pluck("id")[0];

        CommentModel::create(
            [
                'comment'=>$request->comment,
                'assignment_id'=>$id
            ]
        );
        return redirect()->route('marks.index')
            ->with('success', 'Comment Added successfully');
    } 
}
