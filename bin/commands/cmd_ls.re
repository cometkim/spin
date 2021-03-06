open Cmdliner;
open Spin;

let run = () => {
  Template_official.download_if_absent();
  Template_official.update_if_present();
  let templates = Template_official.all();

  Console.log("The official templates are:\n");

  List.iter(
    templates,
    ~f=el => {
      Console.log(
        <Pastel color=Pastel.Blue bold=true> {"    " ++ el.name} </Pastel>,
      );
      Console.log("      " ++ el.description ++ "\n");
    },
  );

  Lwt.return();
};

let cmd = {
  let doc = "List the official spin templates";

  let run_command = () => run |> Errors.handle_errors |> Lwt_main.run;

  Term.(
    app(const(run_command), const()),
    info(
      "ls",
      ~doc,
      ~envs=Man.envs,
      ~version=Man.version,
      ~exits=Man.exits,
      ~man=Man.man,
      ~sdocs=Man.sdocs,
    ),
  );
};
