<?php

namespace App\Http\Controllers;

use App\Models\AssignmentModel;
use App\Models\PupilModel;
use App\Models\User;
use Illuminate\Http\Request;
use App\Models\MarksModel;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Contracts\Support\Renderable
     */
    public function index()
    {
        $totalPupils = PupilModel::all()->count();
        $totalTeachers = User::all()->count();
        $totalAssignments = AssignmentModel::all()->count();
        $totalAttempts = MarksModel::all()->count();
        return view('home', compact('totalPupils', 'totalTeachers', 'totalAssignments','totalAttempts'));
    }
}
