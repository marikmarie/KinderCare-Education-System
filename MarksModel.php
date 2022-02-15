<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class MarksModel extends Model
{
    use HasFactory;
    protected $table = 'marks';
    protected $fillable = [
        'assignment_id',
        'pupil_id',
        'marks',
        'id',
        'comment'

    ];
}
