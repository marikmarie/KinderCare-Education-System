<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\User;

class TeacherController extends Controller
{

    public function index()
    {
        $data =  User::all();
        return view("teachers.index", compact('data'));
    }
}
