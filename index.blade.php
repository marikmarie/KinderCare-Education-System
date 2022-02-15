<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>KinderCare Character Drawing System - KCDS</title>
    <meta name="csrf-token" content="{{ csrf_token() }}" />
    <!-- Google Font: Source Sans Pro -->
    <link rel="stylesheet"
        href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:300,400,400i,700&display=fallback">
    <!-- Font Awesome -->

    <link rel="stylesheet" href="{{ asset('plugins/fontawesome-free/css/all.css') }}">
    <!-- DataTables -->
    <link rel="stylesheet" href="{{ asset('plugins/datatables-bs4/css/dataTables.bootstrap4.min.css') }}">
    <link rel="stylesheet" href="{{ asset('plugins/datatables-responsive/css/responsive.bootstrap4.min.css') }}">
    <link rel="stylesheet" href="{{ asset('plugins/datatables-buttons/css/buttons.bootstrap4.min.css') }}">
    <!-- Theme style -->
    <link rel="stylesheet" href="{{ asset('dist/css/adminlte.min.css') }}">
    <style>
        .style_button {
            background: #657836 !important;
            color: #fff;
            width: 100% !important;
            border: none !important;
            height: 40px !important;
            cursor: pointer;
            border-radius: 10px;
        }


    </style>
    <style>
        .style_button {
            background: #657836 !important;
            color: #fff;
            width: 100% !important;
            border: none !important;
            height: 40px !important;
            cursor: pointer;
            border-radius: 10px;
        }

        .farmer__filter {
            display: flex !important;
            align-items: center !important;
            justify-content: space-evenly !important;
        }
        .platform{
            display: none !important;
        }

        .content-wrapper{
            position: relative !important;
        }
        .image__remove{
            position: absolute !important;
            right: 30px !important;
            top:10px !important;
            cursor: pointer;
        }

    </style>
</head>

<body class="hold-transition sidebar-mini">
    <div class="wrapper">
        @include('navbars.auth.auth')
        <!-- Main Sidebar Container -->
        @include('sidebars.leftsidebar')

        <!-- Content Wrapper. Contains page content -->
        <div class="content-wrapper">

            <!--any wrong info-->
            <div id="content-wrap">
                @if ($message = Session::get('success'))
                <div class="alert alert-success m-4" >
                    <p>{{ $message }}</p>
                    <img src="{{asset('images/remove.png')}}"
             class="image__remove"

            alt="cross image"
             height="20px"
             width="20px"

            >

                </div>
            @endif
            <!--any wrong info-->
            </div>
            <!--any wrong info-->

            <!-- /.card -->
            <!-- Content Header (Page header) -->
            <section class="content-header">
                <div class="container-fluid">
                    <div class="row mb-2">
                        <div class="col-sm-6">
                            <h1>pupils</h1>
                        </div>
                        <div class="col-sm-6">
                            <ol class="breadcrumb float-sm-right">
                                <li class="breadcrumb-item"><a href="{{ route('pupils.index') }}">Home</a></li>
                                <li class="breadcrumb-item active">pupils</li>
                            </ol>
                        </div>
                    </div>
                </div><!-- /.container-fluid -->
            </section>

            <!-- Main content -->
            <section class="content">
                <div class="container-fluid">


                    <div class="row">
                        <div class="col-12">
                            <!--table-->
                            <!-- /.card -->

                            <div class="card">
                                <div class="card-header">
                                    <h3 class="card-title ">pupils</h3>
                                    <h4 class="float-sm-right ">
                                        <a class="btn btn-success" href="{{ route('pupils.create') }}"> Add New Pupil
                                            </a>
                                    </h4>
                                </div>

                                <!--table removed-->
                                <div class="card-body">
                                    <table id="example1" class="table table-bordered table-striped">
                                        <thead>
                                            <tr>
                                                <th>First Name</th>
                                                <th>Second Name</th>
                                                <th>User Code</th>

                                                <th>Phone Number</th>
                                                <th>Status</th>

                                                <th>Actions</th>
                                            </tr>
                                        </thead>
                                        <tbody>

                                            <!--create a tr--->

                                            @foreach ($data as $key => $user)
                                                <tr>
                                                    <td>{{ $user->firstname }}
                                                    </td>
                                                    <td>
                                                        {{ $user->lastname }}
                                                    </td>
                                                    <td>

                                                        {{$user->usercode}}
                                                    </td>


                                                    <td>{{ $user->phoneNumber }}</td>
                                                    <td>
                                                     @if ($user->status == 1)
                                                        <p >Active</p>
                                                         
                                                     @else
                                                           <div>
                                                               <p>Inactive</p>
                                                           </div>
                                                     @endif
                                                    </td>


                                                    <td width="280px">
                                                          @if($user->status ==1)
                                                          <a class="btn btn-danger"

                                                          href="{{route('actonpupil.act', ["id"=>$user->id, "status"=>0])}}">
                                                          Deactivate</a>
                                                          @else
                                                          <a class="btn btn-info"

                                                          href="{{ route('actonpupil.act', ["id"=>$user->id, "status"=>1]) }}">
                                                          Activate</a>
                                                            @if($user->activation_request==1)
                                                                <span class="badge badge-success">Requested Activation</span>
                                                            @endif
                                                          @endif

                                                        

                                                    </td>
                                                </tr>
                                            @endforeach
                                            <!--create a tr--->

                                        </tbody>

                                    </table>
                                </div>


                                <!--table removed-->
                            </div>
                            <!-- /.card -->
                            <!--table-->
                        </div>
                        <!-- /.col -->
                    </div>
                    <!-- /.row -->
                </div>
                <!-- /.container-fluid -->
            </section>
            <!-- /.content -->
        </div>
        <!-- /.content-wrapper -->
        @include('footer.footer')

        <!-- Control Sidebar -->
        <aside class="control-sidebar control-sidebar-dark">
            <!-- Control sidebar content goes here -->
        </aside>
        <!-- /.control-sidebar -->
    </div>
    <!-- ./wrapper -->

    <!-- jQuery -->
    <script src="{{ asset('plugins/jquery/jquery.min.js') }}"></script>
    <!-- Bootstrap 4 -->

    <script src="{{ asset('plugins/bootstrap/js/bootstrap.bundle.min.js') }}"></script>
    <!-- DataTables  & Plugins -->
    <script src="{{ asset('plugins/datatables/jquery.dataTables.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-bs4/js/dataTables.bootstrap4.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-responsive/js/dataTables.responsive.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-responsive/js/responsive.bootstrap4.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-buttons/js/dataTables.buttons.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-buttons/js/buttons.bootstrap4.min.js') }}"></script>
    <script src="{{ asset('plugins/jszip/jszip.min.js') }}"></script>
    <script src="{{ asset('plugins/pdfmake/pdfmake.min.js') }}"></script>
    <script src="{{ asset('plugins/pdfmake/vfs_fonts.js') }}"></script>
    <script src="{{ asset('plugins/datatables-buttons/js/buttons.html5.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-buttons/js/buttons.print.min.js') }}"></script>
    <script src="{{ asset('plugins/datatables-buttons/js/buttons.colVis.min.js') }}"></script>
    <!-- AdminLTE App -->
    <script src="{{ asset('dist/js/adminlte.min.js') }}"></script>
    <!-- AdminLTE for demo purposes -->
    <script src="{{ asset('dist/js/demo.js') }}"></script>
    <!-- Page specific script -->


    <script>
        $(function() {
            $("#example1").DataTable({
                "responsive": true,
                "lengthChange": false,
                "autoWidth": false,
                "buttons": ["copy", "csv", "excel", "pdf"]
            }).buttons().container().appendTo('#example1_wrapper .col-md-6:eq(0)');
            $('#example2').DataTable({
                "paging": true,
                "lengthChange": false,
                "searching": false,
                "ordering": true,
                "info": true,
                "autoWidth": false,
                "responsive": true,
            });
        });
    </script>

        <!--hide alert--->
        <script type="text/javascript">
            $(function(){
                $('.image__remove').click(function(){
                    //alert('clicked')
                    $("#content-wrap").addClass('platform');
                    $("..image__remove").addClass('platform');

                })
            })
           </script>
           <!--hide alert-->


</body>

</html>
