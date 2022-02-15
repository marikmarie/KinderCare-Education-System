<style>
    .sideBar-color {
        background-color: #031223 !important;
        margin-right: 20px !important;
    }

</style>
<!-- Main Sidebar Container -->
<div class="sideBar-color">
    <aside class="main-sidebar sidebar-dark-primary elevation-4 sideBar-color">
        <!-- Brand Logo -->
        <a href="#" class="brand-link">
            <img src="{{ asset('dist/img/logo.jpeg') }}" alt="image" class="brand-image img-circle elevation-3"
                style="opacity: .8">
            <span class="brand-text font-weight-light"> <c><i><b>KCDS</b></i></c> </span>
        </a>

        <!-- Sidebar -->
        <div class="sidebar">
            <!-- Sidebar user panel (optional) -->
            <div class="user-panel mt-3 pb-3 mb-3 d-flex">
                <div class="image">
                    <img src="{{ asset('dist/img/logo.jpeg') }}" class="img-circle elevation-2"
                        alt="User Image">
                </div>
                <div class="info">
                    <a href="#" class="d-block">
                        {{ Auth::user()->name }}</a>
                </div>
            </div>


            <!-- Sidebar Menu -->
            <nav class="mt-2">
                <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu"
                    data-accordion="false">


                    <!---teachers-->

                        <li class="nav-item">
                            <a href="#" class="nav-link">
                                <i class="nav-icon fas fa-user-tie"></i>
                                <p>
                                    Teachers
                                    <i class="right fas fa-angle-left"></i>
                                </p>
                            </a>
                            <ul class="nav nav-treeview">

                                <li class="nav-item">
                                    <a href="{{route('teachers.index')}}" class="nav-link">
                                        <i class="far fa-circle nav-icon"></i>
                                        <p>View Teacher</p>
                                    </a>
                                </li>
                            </ul>


                        </li>

                    <!---teachers-->


                    </li>

                     <!--pupil-->

                     <li class="nav-item">
                        <a href="#" class="nav-link">
                            <i class="nav-icon fas fa-users"></i>
                            <p>
                                Pupils
                                <i class="right fas fa-angle-left"></i>
                            </p>
                        </a>

                        <ul class="nav nav-treeview">

                            <li class="nav-item">
                                <a href="{{route("pupils.create")}}" class="nav-link">
                                    <i class="far fa-circle nav-icon"></i>
                                    <p>Add Pupils</p>
                                </a>
                            </li>
                            <li class="nav-item">
                                <a href="{{route('pupils.index')}}" class="nav-link">
                                    <i class="far fa-circle nav-icon"></i>
                                    <p>View Pupils</p>
                                </a>
                            </li>
                        </ul>
                    </li>
                     <!--pupil-->

                     <!--assignment-->

                     <li class="nav-item">
                        <a href="#" class="nav-link">
                            <i class="nav-icon fas fa-book"></i>
                            <p>
                                Assignment
                                <i class="right fas fa-angle-left"></i>
                            </p>
                        </a>

                        <ul class="nav nav-treeview">

                            <li class="nav-item">
                                <a href="{{route('assignment.create')}}" class="nav-link">
                                    <i class="far fa-circle nav-icon"></i>
                                    <p>Add Assignment</p>
                                </a>
                            </li>
                            <li class="nav-item">
                                <a href="{{route('assignment.index')}}" class="nav-link">
                                    <i class="far fa-circle nav-icon"></i>
                                    <p>View Assignment</p>
                                </a>
                            </li>
                        </ul>
                    </li>
                     <!--asssignment-->






                    <!--reports-->

                        <li class="nav-item">
                            <a href="#" class="nav-link">
                                <i class="nav-icon fas fa-file-word"></i>
                                <p>
                                    Reports
                                    <i class="right fas fa-angle-left"></i>
                                </p>
                            </a>

                            <ul class="nav nav-treeview">

                                <li class="nav-item">
                                    <a href="{{route('reports.attempts')}}" class="nav-link">
                                        <i class="far fa-circle nav-icon"></i>
                                        <p>Attempts Report</p>
                                    </a>
                                </li>
                            </ul>
                        </li>


                    <!--reports-->

                </ul>
            </nav>
            <!-- /.sidebar-menu -->
        </div>
        <!-- /.sidebar -->
    </aside>

</div>
