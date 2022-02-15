<?php

namespace App\Http\Controllers;

use App\Models\PupilModel;
use Illuminate\Http\Request;


class PupilController extends Controller
{
    //
    public function index()
    {
        $data =  PupilModel::all();
    
        return view("pupil.index", compact('data'));
    }

    public function create()
    {
        return view("pupil.create");
    }

    //store student
    public function store(Request $request)
    {
        $this->validate($request, [
            'lname' => 'required',
            'fname' => 'required',
            'code' => 'required',
            'phone' => 'required'
        ]);

        //store pupil
        PupilModel::create([
            "firstname" => $request->fname,
            'lastname' => $request->lname,
            'usercode' => $request->code,
            'phoneNumber' => $request->phone,
            'status' => 1
        ]);
        return redirect()->route('pupils.index')
            ->with('success', 'Pupil Added successfully');
    } 
    //store student

    //deactive and activate
    public function act($id, $status)
    {
        $getPupil = PupilModel::find($id)->update(['status' => $status,'activation_request'=>0]);
        return redirect()->route('pupils.index')
            ->with('success', 'Pupil Status Updated successfully');
    }
}
